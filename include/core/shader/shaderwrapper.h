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

  void build(const std::string &vertexShaderPath,
             const std::string &fragmentShaderPath,
             const std::string &geometryShaderPath);

  void start() const;
  void stop() const;

  void storeUniformLocation();
  void storeAttributeLocation();

  [[nodiscard]] int getUniformLocation(const std::string &name) const;
  [[nodiscard]] std::vector<std::string> getUniformsName() const;
  [[nodiscard]] int getAttributeLocation(const std::string &name) const;

  template <typename T>
  void setUniform(const std::string &structName, const std::string &name,
                  const T &val) {
    std::ostringstream ost;
    ost << structName << "." << name;
    setUniform(ost.str(), val);
  }

  template <typename T>
  void setUniform(const std::string &structName, int index,
                  const std::string &name, const T &val) {
    std::ostringstream ost;
    ost << structName << "[" << index << "]." << name;
    setUniform(ost.str(), val);
  }

  template <typename T>
  void setUniform(const std::string &name, int index, const T &val) {
    std::ostringstream ost;
    ost << name << "[" << index << "]";
    setUniform(ost.str(), val);
  }

  void setUniform(const std::string &name, const glm::vec3 &v);
  void setUniform(const std::string &name, const glm::vec4 &v);
  void setUniform(const std::string &name, const glm::mat3 &m);
  void setUniform(const std::string &name, const glm::mat4 &m);
  void setUniform(const std::string &name, float val);
  void setUniform(const std::string &name, int val);
  void setUniform(const std::string &name, unsigned int val);
  void setUniform(const std::string &name, bool val);

  void bindTexture(const std::string &name, unsigned int id);
  void bindCubeTexture(const std::string &name, unsigned int id);
  void unbindTexture();

  [[nodiscard]] unsigned int getProgramId() const;

 private:
  ShaderProgram _shaderProgram;

  std::unordered_map<std::string, int> _uniformLocations;
  std::unordered_map<std::string, int> _attributeLocations;

  std::unordered_map<std::string, int> texture_bindings_;

  bool AssertUniformExists(const std::string &name) const;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_SHADER_SHADER_WRAPPER_H
