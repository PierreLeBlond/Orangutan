#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "core/shader/shaderhandle.h"

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

#endif  // SHADER_H
