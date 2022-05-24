#ifndef ORANGUTAN_MODEL_ASSETS_FACTORY_H
#define ORANGUTAN_MODEL_ASSETS_FACTORY_H

#include <memory>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "material/shaderstrategy.h"
#include "mesh/mesh.h"
#include "util/util.h"

namespace orangutan {

class AssetsFactory {
 public:
  static std::vector<std::unique_ptr<Mesh>> ImportMeshs(
      const std::string& filename);
  static std::unique_ptr<ShaderWrapper> CreateShaderWrapper(
      const std::string& name, const std::string& vertex_filename,
      const std::string& fragment_filename,
      const std::string& geometry_filename = "");
  static std::unique_ptr<ShaderStrategy> CreateShaderStrategy(
      ShaderWrapper* shader_wrapper, const std::string& name);

 private:
  static std::unique_ptr<Assimp::Importer> mesh_importer_;

  static std::vector<std::unique_ptr<Mesh>> ExtractMeshesFromScene(
      const aiNode& node, const aiScene& scene);
  static std::unique_ptr<Mesh> ExtractMesh(const aiMesh& mesh);
};

}  // namespace orangutan

#endif  // ORANGUTAN_MODEL_ASSETS_FACTORY_H
