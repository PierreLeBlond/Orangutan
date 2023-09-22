#ifndef ORANGUTAN_CORE_SHADER_SHADER_WRAPPER_H
#define ORANGUTAN_CORE_SHADER_SHADER_WRAPPER_H

#include <iostream>
#include <sstream>
#include <unordered_map>

#include "core/shader/shaderprogram.h"
#include "core/texture/texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "object/asset.h"
#include "util/util.h"

#define MAX_LIGHT 8

namespace orangutan {

class ShaderWrapper : public Asset {
 public:
  ShaderWrapper(const std::string &name);

  void Build(const std::vector<std::string> &defines,
             const std::string &vertex_shader_path,
             const std::string &fragment_shader_path,
             const std::string &geometry_shader_path);

  void Start() const;
  void Stop() const;

  void StoreUniformLocation();
  void StoreAttributeLocation();

  [[nodiscard]] int GetUniformLocation(const std::string &name) const;
  [[nodiscard]] std::vector<std::string> GetUniformsName() const;
  [[nodiscard]] int GetAttributeLocation(const std::string &name) const;

  template <typename T>
  void BindUniform(const std::string &structName, const std::string &name,
                   const T &val) {
    std::ostringstream ost;
    ost << structName << "." << name;
    BindUniform(ost.str(), val);
  }

  template <typename T>
  void BindUniform(const std::string &structName, int index,
                   const std::string &name, const T &val) {
    std::ostringstream ost;
    ost << structName << "[" << index << "]." << name;
    BindUniform(ost.str(), val);
  }

  template <typename T>
  void BindUniform(const std::string &name, int index, const T &val) {
    std::ostringstream ost;
    ost << name << "[" << index << "]";
    BindUniform(ost.str(), val);
  }

  void BindUniform(const std::string &name, const glm::vec3 &v);
  void BindUniform(const std::string &name, const glm::vec4 &v);
  void BindUniform(const std::string &name, const glm::mat3 &m);
  void BindUniform(const std::string &name, const glm::mat4 &m);
  void BindUniform(const std::string &name, float val);
  void BindUniform(const std::string &name, int val);
  void BindUniform(const std::string &name, unsigned int val);
  void BindUniform(const std::string &name, bool val);

  void BindTexture(const std::string &name, unsigned int id);
  void BindCubeTexture(const std::string &name, unsigned int id);
  void UnbindTexture();

  [[nodiscard]] unsigned int GetProgramId() const;

 private:
  ShaderProgram shader_program_;

  std::unordered_map<std::string, int> uniform_locations_;
  std::unordered_map<std::string, int> attribute_locations_;

  std::unordered_map<std::string, int> texture_bindings_;

  bool AssertUniformExists(const std::string &name) const;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_WRAPPER_H
