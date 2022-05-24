#include "object/renderableobjectfactory.h"

#include <memory>

#include "material/materialfactory.h"

namespace orangutan {

std::unique_ptr<RenderableObject>
RenderableObjectFactory::CreateRenderableObject(
    const Universe& universe, const std::string& name,
    const std::string& mesh_name, const std::string& material_name,
    const std::string& shader_strategy_name) {
  auto mesh = universe.get_mesh_library().GetItemByName(mesh_name);
  auto material = universe.get_material_library().GetItemByName(material_name);
  auto shader_strategy = universe.get_shader_strategy_library().GetItemByName(
      shader_strategy_name);

  return CreateRenderableObject(name, mesh, material, shader_strategy);
}

std::unique_ptr<RenderableObject>
RenderableObjectFactory::CreateRenderableObject(
    const std::string& name, Mesh* mesh, Material* material,
    ShaderStrategy* shader_strategy) {
  auto renderable_object = std::make_unique<RenderableObject>(name);
  renderable_object->set_mesh(mesh);
  renderable_object->set_material(material);
  renderable_object->set_shader_strategy(shader_strategy);

  return renderable_object;
}

}  // namespace orangutan
