#ifndef ORANGUTAN_MATERIAL_MATERIAL_FACTORY
#define ORANGUTAN_MATERIAL_MATERIAL_FACTORY

#include "assimp/material.h"
#include "material/material.h"
#include "model/universe.h"

namespace orangutan {

class MaterialFactory {
 public:
  static std::unique_ptr<Material> CreatePbrMaterial(const std::string& name);
  static std::unique_ptr<Material> CreateSkyboxMaterial();
  static std::unique_ptr<Material> ExtractMaterial(Universe& universe,
                                                   aiMaterial& material);
};

}  // namespace orangutan

#endif  // ORANGUTAN_MATERIAL_MATERIAL_FACTORY
