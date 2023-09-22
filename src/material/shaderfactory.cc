#include "material/shaderfactory.h"

#include <iterator>
#include <memory>

#include "mesh/meshfactory.h"
#include "object/renderableobjectfactory.h"

namespace orangutan {

std::unique_ptr<ShaderWrapper> ShaderFactory::CreateShaderWrapper(
    const std::string& name, const std::vector<std::string>& defines,
    const std::string& vertexFilename, const std::string& fragmentFilename,
    const std::string& geometryFilename) {
  auto shader_wrapper = std::make_unique<ShaderWrapper>(name);
  shader_wrapper->Build(defines, vertexFilename, fragmentFilename,
                        geometryFilename);
  return shader_wrapper;
}

ShaderWrapper* ShaderFactory::CreateOrGetShaderWrapperFromMaterial(
    Universe& universe, const Material& material,
    const std::vector<std::string>& defines, const std::string& vertex_filename,
    const std::string& fragment_filename,
    const std::string& geometry_filename) {
  std::ostringstream name;

  name << vertex_filename << fragment_filename << geometry_filename;

  auto shader_wrapper =
      universe.get_shader_wrapper_library().GetItemByName(name.str());
  if (shader_wrapper != NULL) {
    return shader_wrapper;
  }

  shader_wrapper = universe.AddShaderWrapper(
      CreateShaderWrapper(name.str(), defines, vertex_filename,
                          fragment_filename, geometry_filename));
  return shader_wrapper;
}

}  // namespace orangutan
