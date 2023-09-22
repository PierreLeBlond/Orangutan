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

  bool Build(const std::vector<std::string> &defines);
  bool Build(const std::vector<std::string> &defines,
             const std::string &vertex_shader_path,
             const std::string &fragment_shader_path,
             const std::string &geometry_shader_path = "");

  bool Attach(unsigned int id);
  bool Link();
  bool Detach(unsigned int id);

  void Start() const;
  void Stop() const;

  [[nodiscard]] unsigned int GetId() const;

 private:
  ShaderProgramHandle handle_;

  Shader vertex_shader_;
  Shader fragment_shader_;
  Shader geometry_shader_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_PROGRAM_H
