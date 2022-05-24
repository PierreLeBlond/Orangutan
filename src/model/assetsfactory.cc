#include "model/assetsfactory.h"

#include <assimp/postprocess.h>

#include <iterator>
#include <memory>

#include "mesh/meshfactory.h"
#include "object/renderableobjectfactory.h"

namespace orangutan {

std::unique_ptr<Assimp::Importer> AssetsFactory::mesh_importer_;

std::vector<std::unique_ptr<Mesh>> AssetsFactory::ExtractMeshesFromScene(
    const aiNode& node, const aiScene& scene) {
  std::vector<std::unique_ptr<Mesh>> meshes;
  for (unsigned int i = 0; i < node.mNumMeshes; i++) {
    aiMesh* mesh = scene.mMeshes[node.mMeshes[i]];
    meshes.push_back(ExtractMesh(*mesh));
  }
  for (unsigned int i = 0; i < node.mNumChildren; i++) {
    auto extracted_meshes = ExtractMeshesFromScene(*node.mChildren[i], scene);
    meshes.insert(meshes.end(),
                  std::make_move_iterator(extracted_meshes.begin()),
                  std::make_move_iterator(extracted_meshes.end()));
  }
  return meshes;
}

std::unique_ptr<Mesh> AssetsFactory::ExtractMesh(const aiMesh& mesh) {
  std::cout << "Extracted mesh `" << mesh.mName.C_Str() << "`" << std::endl;

  auto extracted_mesh = std::make_unique<Mesh>(mesh.mName.C_Str());

  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;

  std::vector<unsigned int> indices;

  for (unsigned int i = 0; i < mesh.mNumVertices; i++) {
    glm::vec3 vertex = glm::vec3(mesh.mVertices[i].x, mesh.mVertices[i].y,
                                 mesh.mVertices[i].z);
    vertices.push_back(vertex);

    glm::vec3 normal =
        glm::vec3(mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z);
    normals.push_back(normal);

    glm::vec2 uv;
    if (mesh.mTextureCoords[0]) {
      uv = glm::vec2(mesh.mTextureCoords[0][i].x, mesh.mTextureCoords[0][i].y);
    }
    uvs.push_back(uv);
  }

  for (unsigned int i = 0; i < mesh.mNumFaces; i++) {
    aiFace face = mesh.mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  extracted_mesh->setPositions(vertices);
  extracted_mesh->setNormals(normals);
  extracted_mesh->setUvs(uvs);
  extracted_mesh->setFaces(indices);

  return extracted_mesh;
}

std::vector<std::unique_ptr<Mesh>> AssetsFactory::ImportMeshs(
    const std::string& filename) {
  if (mesh_importer_.get() == nullptr) {
    mesh_importer_ = std::make_unique<Assimp::Importer>();
  }
  const aiScene* scene = mesh_importer_->ReadFile(
      filename, aiProcess_Triangulate | aiProcess_FlipUVs);

  std::vector<std::unique_ptr<Mesh>> meshs =
      ExtractMeshesFromScene(*scene->mRootNode, *scene);

  return meshs;
}

std::unique_ptr<ShaderWrapper> AssetsFactory::CreateShaderWrapper(
    const std::string& name, const std::string& vertexFilename,
    const std::string& fragmentFilename, const std::string& geometryFilename) {
  auto shader_wrapper = std::make_unique<ShaderWrapper>(name);
  shader_wrapper->build(vertexFilename, fragmentFilename, geometryFilename);
  return shader_wrapper;
}

std::unique_ptr<ShaderStrategy> AssetsFactory::CreateShaderStrategy(
    ShaderWrapper* shader_wrapper, const std::string& name) {
  std::unique_ptr<ShaderStrategy> strategy;
  strategy = std::make_unique<ShaderStrategy>(name);
  strategy->set_shader_wrapper(shader_wrapper);
  strategy->InitAttribute();
  return strategy;
}

}  // namespace orangutan
