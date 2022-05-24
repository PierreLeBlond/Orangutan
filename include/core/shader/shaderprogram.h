#ifndef ORANGUTAN_CORE_SHADER_SHADER_PROGRAM_H
#define ORANGUTAN_CORE_SHADER_SHADER_PROGRAM_H

#include "core/shader/shader.h"
#include "core/shader/shaderprogramhandle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"

#define MAX_LIGHT 8

namespace orangutan {

class ShaderProgram {
 public:
  ShaderProgram();

  bool build();
  bool build(const std::string &vertexShaderPath,
             const std::string &fragmentShaderPath,
             const std::string &geometryShaderPath = "");

  bool attach(unsigned int id);
  bool link();
  bool detach(unsigned int id);

  void start() const;
  void stop() const;

  [[nodiscard]] unsigned int getId() const;

 private:
  ShaderProgramHandle _handle;

  Shader _vertexShader;
  Shader _fragmentShader;
  Shader _geometryShader;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_PROGRAM_H
