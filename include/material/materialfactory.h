#ifndef ORANGUTAN_MATERIAL_MATERIAL_FACTORY
#define ORANGUTAN_MATERIAL_MATERIAL_FACTORY

#include "material/material.h"

namespace orangutan {

class MaterialFactory {
 public:
  static std::unique_ptr<Material> CreatePbrMaterial(const std::string& name);
  static std::unique_ptr<Material> CreateSkyboxMaterial();
};

}  // namespace orangutan

#endif  // ORANGUTAN_MATERIAL_MATERIAL_FACTORY
