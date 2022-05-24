#include "material/materialfactory.h"

#include <algorithm>
#include <memory>

#include "core/texture/cubetexture.h"
#include "core/texture/texture.h"

namespace orangutan {

std::unique_ptr<Material> MaterialFactory::CreatePbrMaterial(
    const std::string& name) {
  auto material = std::make_unique<Material>(name);

  material->CreateUniform("albedo", glm::vec3(1.0f, 1.0f, 1.0f),
                          glm::vec3(0.0f, 0.0f, 0.0f),
                          glm::vec3(1.0f, 1.0f, 1.0f));
  material->CreateUniform("roughness", 1.0f, 0.0f, 1.0f);
  material->CreateUniform("metalness", 0.0f, 0.0f, 1.0f);

  return material;
}

std::unique_ptr<Material> MaterialFactory::CreateSkyboxMaterial() {
  auto material = std::make_unique<Material>("Skybox");
  return material;
}

}  // namespace orangutan
