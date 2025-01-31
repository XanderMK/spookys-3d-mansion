from os import listdir
from os.path import exists, isfile, join
from pathlib import Path

gfxPath = "./3ds/gfx/"

allFiles = [f for f in listdir(gfxPath) if isfile(join(gfxPath, f))]

for file in allFiles:
    if (not (file.endswith(".png") or file.endswith(".jpg") or file.endswith(".jpeg"))) or exists(gfxPath + file.split('.')[0] + ".t3s"): 
        continue

    file_path = Path(gfxPath + file.split('.')[0] + ".t3s")
    with file_path.open("w") as newFile:
        newFile.write("-f auto-etc1 -z auto\n" + file)
        print(file_path)