#ifndef CMAKEGRAPHICSPROJECT_MODEL_H
#define CMAKEGRAPHICSPROJECT_MODEL_H

#include "CommonInclude.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

#include <assimp/scene.h>

class Model
{
public:
    Model(const char* path);

    void draw(const Shader& program) const;

private:
    std::vector<Mesh> _meshes;
    std::string _directory;
    std::vector<Mesh::Texture> _texuresLoaded;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial* material, aiTextureType textureType, const std::string& typeName);
};

#endif
