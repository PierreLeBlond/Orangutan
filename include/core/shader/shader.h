#ifndef ORANGUTAN_CORE_SHADER_SHADER_H
#define ORANGUTAN_CORE_SHADER_SHADER_H

#include <string>

#include "core/shader/shaderhandle.h"

namespace orangutan {

class Shader {
 public:
  Shader(ShaderType type = ShaderType::VERTEX, const std::string& path = "");

  bool Compile(const std::vector<std::string>& defines);
  bool Compile(const std::vector<std::string>& defines,
               const std::string& path);

  [[nodiscard]] unsigned int GetId() const;
  [[nodiscard]] const std::string& GetPath() const;

 private:
  ShaderHandle handle_;
  std::string path_;

  std::string FileToString(const std::string& filename);
  bool PrintShaderInfo(const std::string& msg);
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_H
