#include "mesh.hpp"

Mesh::Mesh(GameObject *parent, std::string &filename) : Component(parent)
{
    this->SetMesh(filename);
}

Mesh::~Mesh() {}

void Mesh::Update(float deltaTime) {};

void Mesh::Render()
{
    for (auto &submesh : this->submeshes)
    {
        // Bind texture
        C3D_TexBind(0, submesh->tex.get());

        // Configure buffer
        C3D_BufInfo* bufInfo = C3D_GetBufInfo();
        BufInfo_Init(bufInfo);
        BufInfo_Add(bufInfo, submesh->vbo, sizeof(Vertex), 3, 0x210);

        // Draw
        C3D_DrawElements(GPU_TRIANGLES, submesh->iboSize, C3D_UNSIGNED_SHORT, submesh->ibo);
    }
}

void Mesh::SetMesh(std::string &filename)
{
    // Clear existing data
    this->submeshes.clear();

    // Load model from file
    ufbx_load_opts opts{};
    opts.target_axes = ufbx_axes_right_handed_y_up;
    opts.target_unit_meters = 0.1f;

    ufbx_error error;
    ufbx_scene *scene = ufbx_load_file(filename.c_str(), &opts, &error);
    if (!scene)
    {
        std::cout << "Error opening file: " << filename << ": " << error.description.data << std::endl;
        return;
    }

    for (auto &mesh : scene->meshes)
    {
        for (unsigned int i = 0; i < mesh->material_parts.count; i++)
        {
            auto submesh = std::make_shared<Submesh>();

            ConvertMeshPart(submesh, *mesh, mesh->material_parts[i]);
            
            std::string filename(mesh->materials[i]->textures[0].texture->absolute_filename.data);
            filename = filename.substr(filename.find_last_of('/') + 1);
            submesh->tex = Textures::GetTexture(filename);

            this->submeshes.push_back(submesh);
        }
    }

    ufbx_free_scene(scene);
}

void Mesh::ConvertMeshPart(std::shared_ptr<Submesh> &submesh, const ufbx_mesh &mesh, const ufbx_mesh_part &part)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> tri_indices;
    tri_indices.resize(mesh.max_face_triangles * 3);

    // Iterate over each face using the specific material.
    for (uint32_t face_index : part.face_indices) {
        ufbx_face face = mesh.faces[face_index];

        // Triangulate the face into `tri_indices[]`.
        uint32_t num_tris = ufbx_triangulate_face(
            tri_indices.data(), tri_indices.size(), &mesh, face);

        // Iterate over each triangle corner contiguously.
        for (size_t i = 0; i < num_tris * 3; i++) {
            uint32_t index = tri_indices[i];

            Vertex v;
            v.position = mesh.vertex_position[index];
            v.normal = mesh.vertex_normal[index];
            v.uv = mesh.vertex_uv[index];
            vertices.push_back(v);
        }
    }

    // Should have written all the vertices.
    assert(vertices.size() == part.num_triangles * 3);

    // Generate the index buffer.
    ufbx_vertex_stream streams[1] = {
        { vertices.data(), vertices.size(), sizeof(Vertex) },
    };
    std::vector<uint32_t> indices;
    indices.resize(part.num_triangles * 3);

    // This call will deduplicate vertices, modifying the arrays passed in `streams[]`,
    // indices are written in `indices[]` and the number of unique vertices is returned.
    size_t num_vertices = ufbx_generate_indices(
        streams, 1, indices.data(), indices.size(), nullptr, nullptr);

    // Trim to only unique vertices.
    vertices.resize(num_vertices);

    std::vector<unsigned short> shortIndices(indices.begin(), indices.end());
    
    submesh->vbo = (Vertex*)linearAlloc(vertices.size() * sizeof(Vertex));
    submesh->ibo = (unsigned short*)linearAlloc(shortIndices.size() * sizeof(unsigned short));

    submesh->vboSize = vertices.size() * 8;
    submesh->iboSize = shortIndices.size();

    memcpy(submesh->vbo, vertices.data(), vertices.size() * sizeof(Vertex));
    memcpy(submesh->ibo, shortIndices.data(), shortIndices.size() * sizeof(unsigned short));
}