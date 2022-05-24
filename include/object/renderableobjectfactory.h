#ifndef ORANGUTAN_OBJECT_RENDERABLE_OBJECT_FACTORY_H
#define ORANGUTAN_OBJECT_RENDERABLE_OBJECT_FACTORY_H

#include <memory>
#include <vector>

#include "model/universe.h"

namespace orangutan {

class RenderableObjectFactory {
 public:
  static std::unique_ptr<RenderableObject> CreateRenderableObject(
      const Universe& universe, const std::string& name,
      const std::string& mesh_name, const std::string& material_name,
      const std::string& shader_strategy_name);

  static std::unique_ptr<RenderableObject> CreateRenderableObject(
      const std::string& name, Mesh* mesh, Material* material,
      ShaderStrategy* shader_strategy);
};

}  // namespace orangutan

#endif  // ORANGUTAN_OBJECT_RENDERABLE_OBJECT_FACTORY_H
