#ifndef ORANGUTAN_CORE_SHADER_SHADER_H
#define ORANGUTAN_CORE_SHADER_SHADER_H

#include <string>

#include "core/shader/shaderhandle.h"

namespace orangutan {

class Shader {
 public:
  Shader(ShaderType type = ShaderType::VERTEX, const std::string& path = "");

  bool compile();
  bool compile(const std::string& path);

  [[nodiscard]] unsigned int getId() const;
  [[nodiscard]] const std::string& getPath() const;

 private:
  ShaderHandle _handle;
  std::string _path;

  std::string fileToString(const std::string& filename);
  bool printShaderInfo(const std::string& msg);
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_H
