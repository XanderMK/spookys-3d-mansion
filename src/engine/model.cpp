#include "model.hpp"

// basically copied from ufbx docs lol
void Model::ConvertModelPart(std::shared_ptr<Submodel> &submodel, const ufbx_mesh &mesh, const ufbx_mesh_part &part)
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
    
    submodel->vbo = (Vertex*)linearAlloc(vertices.size() * sizeof(Vertex));
    submodel->ibo = (unsigned short*)linearAlloc(shortIndices.size() * sizeof(unsigned short));

    submodel->vboSize = vertices.size() * 8;
    submodel->iboSize = shortIndices.size();

    memcpy(submodel->vbo, vertices.data(), vertices.size() * sizeof(Vertex));
    memcpy(submodel->ibo, shortIndices.data(), shortIndices.size() * sizeof(unsigned short));
}

void Model::SetSubmodelMaterial(std::shared_ptr<Submodel> &submodel, ufbx_material &mat)
{
    submodel->mat = C3D_Material{0};

    // Models don't contain definition for ambient color, set it to default of 0.1
    const float defaultAmbientColor[3] = {0.1f, 0.1f, 0.1f};
    memcpy(submodel->mat.ambient, defaultAmbientColor, sizeof(float[3]));
    
    // Copy base color (diffuse)
    if (mat.pbr.base_color.has_value)
    {
        memcpy(submodel->mat.diffuse, mat.pbr.base_color.value_vec3.v, sizeof(float[3]));
    }
    else
    {
        const float defaultBaseColor[3] = {1.f, 1.f, 1.f}; 
        memcpy(submodel->mat.diffuse, defaultBaseColor, sizeof(float[3]));
    }

    // Copy specular
    if (mat.pbr.specular_color.has_value)
    {
        // Multiply color by specular factor
        memcpy(submodel->mat.specular0, mat.pbr.specular_color.value_vec3.v, sizeof(float[3]));
        submodel->mat.specular0[0] *= mat.pbr.specular_factor.value_real;
        submodel->mat.specular0[1] *= mat.pbr.specular_factor.value_real;
        submodel->mat.specular0[2] *= mat.pbr.specular_factor.value_real;

        // Color values are reversed; flip them
        float temp = submodel->mat.specular0[0];
        submodel->mat.specular0[0] = submodel->mat.specular0[2];
        submodel->mat.specular0[2] = temp;
    }

    // Copy emission
    if (mat.pbr.emission_color.has_value)
    {
        // Multiply color by emission factor
        memcpy(submodel->mat.emission, mat.pbr.emission_color.value_vec3.v, sizeof(float[3]));
        submodel->mat.emission[0] *= mat.pbr.emission_factor.value_real;
        submodel->mat.emission[1] *= mat.pbr.emission_factor.value_real;
        submodel->mat.emission[2] *= mat.pbr.emission_factor.value_real;

        // Color values are reversed; flip them
        float temp = submodel->mat.emission[0];
        submodel->mat.emission[0] = submodel->mat.emission[2];
        submodel->mat.emission[2] = temp;
    }
}