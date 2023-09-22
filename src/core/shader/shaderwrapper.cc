#include "core/shader/shaderwrapper.h"

#include <nanogui/opengl.h>

namespace orangutan {

ShaderWrapper::ShaderWrapper(const std::string &name) : Asset(name) {}

bool ShaderWrapper::AssertUniformExists(const std::string &name) const {
  return uniform_locations_.find(name) != uniform_locations_.end();
}

void ShaderWrapper::Build(const std::vector<std::string> &defines,
                          const std::string &vertex_shader_path,
                          const std::string &fragment_shader_path,
                          const std::string &geometry_shader_path) {
  if (!shader_program_.Build(defines, vertex_shader_path, fragment_shader_path,
                             geometry_shader_path)) {
    // TODO: print explicit error
    std::cerr << "build error" << std::endl;
  }
  StoreAttributeLocation();
  StoreUniformLocation();
}

void ShaderWrapper::Start() const { shader_program_.Start(); }

void ShaderWrapper::Stop() const { shader_program_.Stop(); }

void ShaderWrapper::StoreUniformLocation() {
  GLint nbOfUniforms = 0;
  glGetProgramInterfaceiv(shader_program_.GetId(), GL_UNIFORM,
                          GL_ACTIVE_RESOURCES, &nbOfUniforms);

  GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};

  for (int i = 0; i < nbOfUniforms; i++) {
    GLint results[4];
    glGetProgramResourceiv(shader_program_.GetId(), GL_UNIFORM, i, 4,
                           properties, 4, NULL, results);
    if (results[3] != -1) {
    }
    GLint nameBufSize = results[0] + 1;
    char *name = new char[nameBufSize];
    glGetProgramResourceName(shader_program_.GetId(), GL_UNIFORM, i,
                             nameBufSize, NULL, name);
    uniform_locations_[std::string(name)] = results[2];
    delete[] name;
  }
}

void ShaderWrapper::StoreAttributeLocation() {
  GLint nbOfAttributes = 0;
  glGetProgramInterfaceiv(shader_program_.GetId(), GL_PROGRAM_INPUT,
                          GL_ACTIVE_RESOURCES, &nbOfAttributes);

  GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

  for (int i = 0; i < nbOfAttributes; i++) {
    GLint results[3];
    glGetProgramResourceiv(shader_program_.GetId(), GL_PROGRAM_INPUT, i, 4,
                           properties, 3, NULL, results);
    GLint nameBufSize = results[0] + 1;
    char *name = new char[nameBufSize];
    glGetProgramResourceName(shader_program_.GetId(), GL_PROGRAM_INPUT, i,
                             nameBufSize, NULL, name);
    attribute_locations_[std::string(name)] = results[2];
    delete[] name;
  }
}

int ShaderWrapper::GetUniformLocation(const std::string &name) const {
  auto it = uniform_locations_.find(name);
  if (it != uniform_locations_.end())
    return it->second;
  else {
    return -1;
  }
}

std::vector<std::string> ShaderWrapper::GetUniformsName() const {
  std::vector<std::string> names;
  for (auto const &p : uniform_locations_) {
    names.push_back(p.first);
  }
  return names;
}

int ShaderWrapper::GetAttributeLocation(const std::string &name) const {
  auto it = attribute_locations_.find(name);
  if (it != attribute_locations_.end())
    return it->second;
  else {
    std::cerr << "Could not find attribute location of : " << name << std::endl;
    return -1;
  }
}

void ShaderWrapper::BindUniform(const std::string &name, const glm::vec3 &v) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform3fv(uniform_locations_[name], 1, glm::value_ptr(v));
}

void ShaderWrapper::BindUniform(const std::string &name, const glm::vec4 &v) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform4fv(uniform_locations_[name], 1, glm::value_ptr(v));
}

void ShaderWrapper::BindUniform(const std::string &name, const glm::mat3 &m) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniformMatrix3fv(uniform_locations_[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderWrapper::BindUniform(const std::string &name, const glm::mat4 &m) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniformMatrix4fv(uniform_locations_[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderWrapper::BindUniform(const std::string &name, float val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1f(uniform_locations_[name], val);
}

void ShaderWrapper::BindUniform(const std::string &name, int val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1i(uniform_locations_[name], val);
}

void ShaderWrapper::BindUniform(const std::string &name, unsigned int val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1ui(uniform_locations_[name], val);
}

void ShaderWrapper::BindUniform(const std::string &name, bool val) {
  if (!AssertUniformExists(name)) {
    return;
  }
  glUniform1i(uniform_locations_[name], val);
}

void ShaderWrapper::BindTexture(const std::string &name, unsigned int id) {
  // Looks like we can't introspectively get samplers names before we want to
  // bind them
  if (texture_bindings_.find(name) == texture_bindings_.end()) {
    texture_bindings_[name] = texture_bindings_.size();
    glUniform1i(uniform_locations_[name], texture_bindings_[name]);
  }
  glActiveTexture(GL_TEXTURE0 + texture_bindings_[name]);
  glBindTexture(GL_TEXTURE_2D, id);
}

void ShaderWrapper::BindCubeTexture(const std::string &name, unsigned int id) {
  if (texture_bindings_.find(name) == texture_bindings_.end()) {
    texture_bindings_[name] = texture_bindings_.size();
    glUniform1i(uniform_locations_[name], texture_bindings_[name]);
  }
  glActiveTexture(GL_TEXTURE0 + texture_bindings_[name]);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void ShaderWrapper::UnbindTexture() {
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

unsigned int ShaderWrapper::GetProgramId() const {
  return shader_program_.GetId();
}

}  // namespace orangutan
