#ifndef ORANGUTAN_OBJECT_RENDERABLE_OBJECT_FACTORY_H
#define ORANGUTAN_OBJECT_RENDERABLE_OBJECT_FACTORY_H

#include <memory>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "model/universe.h"

namespace orangutan {

class RenderableObjectFactory {
 public:
  static std::unique_ptr<RenderableObject> CreateRenderableObject(
      const Universe& universe, const std::string& name,
      const std::string& mesh_name, const std::string& material_name);

  static std::unique_ptr<RenderableObject> CreateRenderableObject(
      const std::string& name, Mesh* mesh, Material* material);

  static std::vector<std::unique_ptr<Mesh>> ImportMeshs(
      Assimp::Importer& importer, const std::string& filename);

 private:
  static std::vector<std::unique_ptr<Mesh>> ExtractMeshesFromScene(
      const aiNode& node, const aiScene& scene);
};

}  // namespace orangutan

#endif  // ORANGUTAN_OBJECT_RENDERABLE_OBJECT_FACTORY_H
