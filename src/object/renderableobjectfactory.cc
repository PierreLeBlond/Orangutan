#include "object/renderableobjectfactory.h"

#include <assimp/postprocess.h>

#include <memory>

#include "material/materialfactory.h"
#include "mesh/meshfactory.h"

namespace orangutan {

std::unique_ptr<RenderableObject>
RenderableObjectFactory::CreateRenderableObject(
    const Universe& universe, const std::string& name,
    const std::string& mesh_name, const std::string& material_name) {
  auto mesh = universe.get_mesh_library().GetItemByName(mesh_name);
  auto material = universe.get_material_library().GetItemByName(material_name);

  return CreateRenderableObject(name, mesh, material);
}

std::unique_ptr<RenderableObject>
RenderableObjectFactory::CreateRenderableObject(const std::string& name,
                                                Mesh* mesh,
                                                Material* material) {
  auto renderable_object = std::make_unique<RenderableObject>(name);
  renderable_object->set_mesh(mesh);
  renderable_object->set_material(material);
  renderable_object->UpdateVertexArrayObject();

  return renderable_object;
}

}  // namespace orangutan
