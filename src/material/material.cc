#include "material/material.h"

namespace orangutan {

Material::Material(const std::string& name) : Asset(name) {}

void Material::AddUniform(const Uniform<float>& u) {
  AddUniform(u, uniforms_1f_);
}

void Material::AddUniform(const Uniform<int>& u) {
  AddUniform(u, uniforms_1i_);
}

void Material::AddUniform(const Uniform<unsigned int>& u) {
  AddUniform(u, uniforms_1ui_);
}

void Material::AddUniform(const Uniform<bool>& u) {
  AddUniform(u, uniforms_1b_);
}

void Material::AddUniform(const Uniform<glm::vec3>& u) {
  AddUniform(u, uniforms_3f_);
}

void Material::AddUniform(const Uniform<glm::vec4>& u) {
  AddUniform(u, uniforms_4f_);
}

void Material::AddUniform(const Uniform<glm::mat3>& u) {
  AddUniform(u, uniforms_3x3_);
}

void Material::AddUniform(const Uniform<glm::mat4>& u) {
  AddUniform(u, uniforms_4x4_);
}

void Material::AddTexture(const std::string& name, const Texture* texture) {
  if (textures_.count(name) == 1) {
    std::cerr << "Texture with name " << texture->getName()
              << " already exist on material " << getName() << std::endl;
  }
  textures_.insert(std::make_pair(name, texture));
}

void Material::AddCubeTexture(const std::string& name,
                              const CubeTexture* cube_texture) {
  if (cube_textures_.count(name) == 1) {
    std::cerr << "Cube texture with name " << cube_texture->getName()
              << " already exist on material " << getName() << std::endl;
  }
  cube_textures_.insert(std::make_pair(name, cube_texture));
}

void Material::SetUniform(const std::string& name, float value) {
  SetUniform(name, value, uniforms_1f_);
}

void Material::SetUniform(const std::string& name, int value) {
  SetUniform(name, value, uniforms_1i_);
}

void Material::SetUniform(const std::string& name, unsigned int value) {
  SetUniform(name, value, uniforms_1ui_);
}

void Material::SetUniform(const std::string& name, bool value) {
  SetUniform(name, value, uniforms_1b_);
}

void Material::SetUniform(const std::string& name, const glm::vec3& value) {
  SetUniform(name, value, uniforms_3f_);
}

void Material::SetUniform(const std::string& name, const glm::vec4& value) {
  SetUniform(name, value, uniforms_4f_);
}

void Material::SetUniform(const std::string& name, const glm::mat3& value) {
  SetUniform(name, value, uniforms_3x3_);
}

void Material::SetUniform(const std::string& name, const glm::mat4& value) {
  SetUniform(name, value, uniforms_4x4_);
}

void Material::SetTexture(const std::string& name, const Texture* texture) {
  auto it = textures_.find(name);
  if (it == textures_.end()) {
    std::cerr << "Texture " << name << " does not exists on material "
              << getName() << std::endl;
  }
  it->second = texture;
}

void Material::SetCubeTexture(const std::string& name,
                              const CubeTexture* cube_texture) {
  auto it = cube_textures_.find(name);
  if (it == cube_textures_.end()) {
    std::cerr << "Cube texture " << name << " does not exists on material "
              << getName() << std::endl;
  }
  it->second = std::move(cube_texture);
}

void Material::GetUniform(const std::string& name, float& value) const {
  GetUniform(name, value, uniforms_1f_);
}

void Material::GetUniform(const std::string& name, int& value) const {
  GetUniform(name, value, uniforms_1i_);
}

void Material::GetUniform(const std::string& name, unsigned int& value) const {
  GetUniform(name, value, uniforms_1ui_);
}

void Material::GetUniform(const std::string& name, bool& value) const {
  GetUniform(name, value, uniforms_1b_);
}

void Material::GetUniform(const std::string& name, glm::vec3& value) const {
  GetUniform(name, value, uniforms_3f_);
}

void Material::GetUniform(const std::string& name, glm::vec4& value) const {
  GetUniform(name, value, uniforms_4f_);
}

void Material::GetUniform(const std::string& name, glm::mat3& value) const {
  GetUniform(name, value, uniforms_3x3_);
}

void Material::GetUniform(const std::string& name, glm::mat4& value) const {
  GetUniform(name, value, uniforms_4x4_);
}

const Texture& Material::GetTexture(const std::string& name) const {
  auto it = textures_.find(name);
  if (it == textures_.end()) {
    std::cerr << "Texture " << name << " does not exists on material "
              << getName() << std::endl;
  }
  return *it->second;
}

const CubeTexture& Material::GetCubeTexture(const std::string& name) const {
  auto it = cube_textures_.find(name);
  if (it == cube_textures_.end()) {
    std::cerr << "Cube texture " << name << " does not exists on material "
              << getName() << std::endl;
  }
  return *it->second;
}

const std::unordered_map<std::string, Uniform<float>>&
Material::get_uniforms_1f() const {
  return uniforms_1f_;
}

const std::unordered_map<std::string, Uniform<int>>& Material::get_uniforms_1i()
    const {
  return uniforms_1i_;
}

const std::unordered_map<std::string, Uniform<unsigned int>>&
Material::get_uniforms_1ui() const {
  return uniforms_1ui_;
}

const std::unordered_map<std::string, Uniform<bool>>&
Material::get_uniforms_1b() const {
  return uniforms_1b_;
}

const std::unordered_map<std::string, Uniform<glm::vec3>>&
Material::get_uniforms_3f() const {
  return uniforms_3f_;
}

const std::unordered_map<std::string, Uniform<glm::vec4>>&
Material::get_uniforms_4f() const {
  return uniforms_4f_;
}

const std::unordered_map<std::string, Uniform<glm::mat3>>&
Material::get_uniforms_3x3() const {
  return uniforms_3x3_;
}

const std::unordered_map<std::string, Uniform<glm::mat4>>&
Material::get_uniforms_4x4() const {
  return uniforms_4x4_;
}

const std::unordered_map<std::string, const Texture*>& Material::get_textures()
    const {
  return textures_;
}

const std::unordered_map<std::string, const CubeTexture*>&
Material::get_cube_textures() const {
  return cube_textures_;
}

}  // namespace orangutan
