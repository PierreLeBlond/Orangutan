#include "core/shader/shaderwrapper.h"

#include <nanogui/opengl.h>

namespace orangutan {

ShaderWrapper::ShaderWrapper(const std::string &name) : Asset(name) {}

bool ShaderWrapper::AssertUniformExists(const std::string &name) const {
  return _uniformLocations.find(name) != _uniformLocations.end();
}

void ShaderWrapper::build(const std::string &vertexShaderPath,
                          const std::string &fragmentShaderPath,
                          const std::string &geometryShaderPath) {
  if (!_shaderProgram.build(vertexShaderPath, fragmentShaderPath,
                            geometryShaderPath)) {
    // TODO: print explicit error
    std::cerr << "build error" << std::endl;
  }
  storeAttributeLocation();
  storeUniformLocation();
}

void ShaderWrapper::start() const { _shaderProgram.start(); }

void ShaderWrapper::stop() const { _shaderProgram.stop(); }

void ShaderWrapper::storeUniformLocation() {
  GLint nbOfUniforms = 0;
  glGetProgramInterfaceiv(_shaderProgram.getId(), GL_UNIFORM,
                          GL_ACTIVE_RESOURCES, &nbOfUniforms);

  GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

  for (int i = 0; i < nbOfUniforms; i++) {
    GLint results[4];
    glGetProgramResourceiv(_shaderProgram.getId(), GL_UNIFORM, i, 4, properties,
                           4, NULL, results);
    if (results[3] != -1) {
    }
    GLint nameBufSize = results[0] + 1;
    char *name = new char[nameBufSize];
    glGetProgramResourceName(_shaderProgram.getId(), GL_UNIFORM, i, nameBufSize,
                             NULL, name);
    _uniformLocations[std::string(name)] = results[2];
    delete[] name;
  }
}

void ShaderWrapper::storeAttributeLocation() {
  GLint nbOfAttributes = 0;
  glGetProgramInterfaceiv(_shaderProgram.getId(), GL_PROGRAM_INPUT,
                          GL_ACTIVE_RESOURCES, &nbOfAttributes);

  GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

  for (int i = 0; i < nbOfAttributes; i++) {
    GLint results[3];
    glGetProgramResourceiv(_shaderProgram.getId(), GL_PROGRAM_INPUT, i, 4,
                           properties, 3, NULL, results);
    GLint nameBufSize = results[0] + 1;
    char *name = new char[nameBufSize];
    glGetProgramResourceName(_shaderProgram.getId(), GL_PROGRAM_INPUT, i,
                             nameBufSize, NULL, name);
    _attributeLocations[std::string(name)] = results[2];
    delete[] name;
  }
}

int ShaderWrapper::getUniformLocation(const std::string &name) const {
  auto it = _uniformLocations.find(name);
  if (it != _uniformLocations.end())
    return it->second;
  else {
    return -1;
  }
}

std::vector<std::string> ShaderWrapper::getUniformsName() const {
  std::vector<std::string> names;
  for (auto const &p : _uniformLocations) {
    names.push_back(p.first);
  }
  return names;
}

int ShaderWrapper::getAttributeLocation(const std::string &name) const {
  auto it = _attributeLocations.find(name);
  if (it != _attributeLocations.end())
    return it->second;
  else {
    std::cerr << "Could not find attribute location of : " << name << std::endl;
    return -1;
  }
}

void ShaderWrapper::setUniform(const std::string &name, const glm::vec3 &v) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform3fv(_uniformLocations[name], 1, glm::value_ptr(v));
}

void ShaderWrapper::setUniform(const std::string &name, const glm::vec4 &v) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform4fv(_uniformLocations[name], 1, glm::value_ptr(v));
}

void ShaderWrapper::setUniform(const std::string &name, const glm::mat3 &m) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniformMatrix3fv(_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderWrapper::setUniform(const std::string &name, const glm::mat4 &m) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniformMatrix4fv(_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderWrapper::setUniform(const std::string &name, float val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1f(_uniformLocations[name], val);
}

void ShaderWrapper::setUniform(const std::string &name, int val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1i(_uniformLocations[name], val);
}

void ShaderWrapper::setUniform(const std::string &name, unsigned int val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1ui(_uniformLocations[name], val);
}

void ShaderWrapper::setUniform(const std::string &name, bool val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1i(_uniformLocations[name], val);
}

void ShaderWrapper::bindTexture(const std::string &name, unsigned int id) {
  // Looks like we can't introspectively get samplers names before we want to
  // bind them
  if (texture_bindings_.find(name) == texture_bindings_.end()) {
    texture_bindings_[name] = texture_bindings_.size();
    glUniform1i(_uniformLocations[name], texture_bindings_[name]);
  }
  glActiveTexture(GL_TEXTURE0 + texture_bindings_[name]);
  glBindTexture(GL_TEXTURE_2D, id);
}

void ShaderWrapper::bindCubeTexture(const std::string &name, unsigned int id) {
  if (texture_bindings_.find(name) == texture_bindings_.end()) {
    texture_bindings_[name] = texture_bindings_.size();
    glUniform1i(_uniformLocations[name], texture_bindings_[name]);
  }
  glActiveTexture(GL_TEXTURE0 + texture_bindings_[name]);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void ShaderWrapper::unbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

unsigned int ShaderWrapper::getProgramId() const {
  return _shaderProgram.getId();
}

}  // namespace orangutan
