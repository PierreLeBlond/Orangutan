#include "scene/scenefactory.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "assimp/postprocess.h"
#include "material/materialfactory.h"
#include "mesh/meshfactory.h"
#include "scene/objectnodefactory.h"

namespace orangutan {

std::unique_ptr<ObjectNode> SceneFactory::ImportSceneTree(
    Assimp::Importer& importer, Universe& universe, const std::string& name,
    const std::string& url) {
  const aiScene* scene =
      importer.ReadFile(url, aiProcess_Triangulate | aiProcess_FlipUVs |
                                 aiProcess_CalcTangentSpace);
  CleanAssimpScene(scene);

  // Extract materials
  for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
    aiMaterial* material = scene->mMaterials[i];
    universe.AddMaterial(MaterialFactory::ExtractMaterial(universe, *material));
  }

  std::unique_ptr<ObjectNode> scene_tree =
      ExtractSceneTree(universe, *scene, *scene->mRootNode);

  return scene_tree;
}

std::unique_ptr<ObjectNode> SceneFactory::ExtractSceneTree(
    Universe& universe, const aiScene& assimp_scene,
    const aiNode& assimp_node) {
  auto node = ObjectNodeFactory::ExtractObjectNode(assimp_node);

  std::vector<std::unique_ptr<Mesh>> meshes;
  for (unsigned int i = 0; i < assimp_node.mNumMeshes; i++) {
    // 1. Retrieve assimp mesh
    aiMesh* assimp_mesh = assimp_scene.mMeshes[assimp_node.mMeshes[i]];
    const std::string mesh_name = assimp_mesh->mName.C_Str();

    // 2. Store mesh
    auto mesh = universe.AddMesh(MeshFactory::ExtractMesh(*assimp_mesh));

    // 3. Get corresponding material
    const std::string material_name =
        assimp_scene.mMaterials[assimp_mesh->mMaterialIndex]->GetName().C_Str();
    auto material =
        universe.get_material_library().GetItemByName(material_name);

    // 4. Create renderable object
    auto renderable_object = universe.AddRenderableObject(
        std::make_unique<RenderableObject>(mesh->getName()));
    renderable_object->set_mesh(mesh);
    renderable_object->set_material(material);
    renderable_object->UpdateVertexArrayObject();

    // 5. Create renderable object node
    const std::string renderable_object_node_name = mesh->getName() + "_node";
    auto renderable_object_node = universe.AddObjectNode(
        std::make_unique<ObjectNode>(renderable_object_node_name));
    renderable_object_node->set_object(renderable_object);

    node->AddChild(renderable_object_node);
  }

  for (unsigned int i = 0; i < assimp_node.mNumChildren; i++) {
    auto child_node = universe.AddObjectNode(
        ExtractSceneTree(universe, assimp_scene, *assimp_node.mChildren[i]));
    node->AddChild(child_node);
  }

  return node;
}

void SceneFactory::CleanAssimpScene(const aiScene* assimp_scene) {
  std::unordered_map<std::string, std::vector<aiMesh*>>
      identically_named_meshes;

  // Avoid duplicated names
  for (unsigned int i = 0; i < assimp_scene->mNumMeshes; i++) {
    auto mesh = assimp_scene->mMeshes[i];
    std::string name = mesh->mName.C_Str();

    const unsigned int count = identically_named_meshes.count(name);
    if (count > 0) {
      identically_named_meshes.at(name).push_back(mesh);
    } else {
      std::vector<aiMesh*> meshes;
      meshes.push_back(mesh);
      identically_named_meshes.insert(std::make_pair(name, meshes));
    }
  }

  for (auto pair : identically_named_meshes) {
    for (unsigned int i = 0; i < pair.second.size(); i++) {
      auto mesh = pair.second[i];
      std::string name = mesh->mName.C_Str();
      mesh->mName = name + "_" + std::to_string(i);
    }
  }
}

}  // namespace orangutan
