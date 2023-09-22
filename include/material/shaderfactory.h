#ifndef ORANGUTAN_MATERIAL_SHADER_FACTORY_H
#define ORANGUTAN_MATERIAL_SHADER_FACTORY_H

#include <memory>
#include <vector>

#include "model/universe.h"
#include "util/util.h"

namespace orangutan {

class ShaderFactory {
 public:
  static std::unique_ptr<ShaderWrapper> CreateShaderWrapper(
      const std::string& name, const std::vector<std::string>& defines,
      const std::string& vertex_filename, const std::string& fragment_filename,
      const std::string& geometry_filename = "");

  static ShaderWrapper* CreateOrGetShaderWrapperFromMaterial(
      Universe& universe, const Material& material,
      const std::vector<std::string>& defines,
      const std::string& vertex_filename, const std::string& fragment_filename,
      const std::string& geometry_filename = "");
};

}  // namespace orangutan

#endif  // ORANGUTAN_MATERIAL_SHADER_FACTORY_H
