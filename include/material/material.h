#ifndef ORANGUTAN_MATERIAL_MATERIAL_H
#define ORANGUTAN_MATERIAL_MATERIAL_H

#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "core/texture/cubetexture.h"
#include "core/texture/texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "material/uniform.h"
#include "object/asset.h"

namespace orangutan {

class Material : public Asset {
 public:
  Material(const std::string& name);

  template <class T>
  void CreateUniform(const std::string& name, const T& value = T(),
                     const T& minValue = T(), const T& maxValue = T()) {
    Uniform<T> uniform(name, value, minValue, maxValue);
    AddUniform(uniform);  // implement move semantic
  }

  template <class T>
  void AddUniform(const Uniform<T>& uniform,
                  std::unordered_map<std::string, Uniform<T>>& uniforms) {
    if (uniforms.count(uniform.getName()) == 1) {
      std::cerr << "Uniform with name " << uniform.getName()
                << " already exist on material " << getName() << std::endl;
    }
    uniforms.insert(std::make_pair(uniform.getName(), uniform));
  }

  void AddUniform(const Uniform<float>& u);
  void AddUniform(const Uniform<int>& u);
  void AddUniform(const Uniform<unsigned int>& u);
  void AddUniform(const Uniform<bool>& u);
  void AddUniform(const Uniform<glm::vec3>& u);
  void AddUniform(const Uniform<glm::vec4>& u);
  void AddUniform(const Uniform<glm::mat3>& u);
  void AddUniform(const Uniform<glm::mat4>& u);

  void AddTexture(const std::string& name, const Texture* texture);
  void AddCubeTexture(const std::string& name, const CubeTexture* texture);

  template <class T>
  void SetUniform(const std::string& name, const T& value,
                  std::unordered_map<std::string, Uniform<T>>& uniforms) {
    auto it = uniforms.find(name);
    if (it == uniforms.end()) {
      std::cerr << "Uniform " << name << " does not exists on material "
                << getName() << std::endl;
    }
    it->second.setValue(value);
  }

  void SetUniform(const std::string& name, float value);
  void SetUniform(const std::string& name, int value);
  void SetUniform(const std::string& name, unsigned int value);
  void SetUniform(const std::string& name, bool value);
  void SetUniform(const std::string& name, const glm::vec3& value);
  void SetUniform(const std::string& name, const glm::vec4& value);
  void SetUniform(const std::string& name, const glm::mat3& value);
  void SetUniform(const std::string& name, const glm::mat4& value);

  void SetTexture(const std::string& name, const Texture* texture);
  void SetCubeTexture(const std::string& name, const CubeTexture* texture);

  template <class T>
  void GetUniform(
      const std::string& name, T& value,
      const std::unordered_map<std::string, Uniform<T>>& uniforms) const {
    auto it = uniforms.find(name);
    if (it == uniforms.end()) {
      std::cerr << "Uniform " << name << " does not exists on material "
                << getName() << std::endl;
    }
    value = it->second.getValue();
  }

  void GetUniform(const std::string& name, float& value) const;
  void GetUniform(const std::string& name, int& value) const;
  void GetUniform(const std::string& name, unsigned int& value) const;
  void GetUniform(const std::string& name, bool& value) const;
  void GetUniform(const std::string& name, glm::vec3& value) const;
  void GetUniform(const std::string& name, glm::vec4& value) const;
  void GetUniform(const std::string& name, glm::mat3& value) const;
  void GetUniform(const std::string& name, glm::mat4& value) const;

  [[nodiscard]] const Texture& GetTexture(const std::string& name) const;
  [[nodiscard]] const CubeTexture& GetCubeTexture(
      const std::string& name) const;

  [[nodiscard]] const std::unordered_map<std::string, Uniform<float>>&
  get_uniforms_1f() const;
  [[nodiscard]] const std::unordered_map<std::string, Uniform<int>>&
  get_uniforms_1i() const;
  [[nodiscard]] const std::unordered_map<std::string, Uniform<unsigned int>>&
  get_uniforms_1ui() const;
  [[nodiscard]] const std::unordered_map<std::string, Uniform<bool>>&
  get_uniforms_1b() const;
  [[nodiscard]] const std::unordered_map<std::string, Uniform<glm::vec3>>&
  get_uniforms_3f() const;
  [[nodiscard]] const std::unordered_map<std::string, Uniform<glm::vec4>>&
  get_uniforms_4f() const;
  [[nodiscard]] const std::unordered_map<std::string, Uniform<glm::mat3>>&
  get_uniforms_3x3() const;
  [[nodiscard]] const std::unordered_map<std::string, Uniform<glm::mat4>>&
  get_uniforms_4x4() const;

  [[nodiscard]] const std::unordered_map<std::string, const Texture*>&
  get_textures() const;
  [[nodiscard]] const std::unordered_map<std::string, const CubeTexture*>&
  get_cube_textures() const;

 private:
  std::unordered_map<std::string, Uniform<float>> uniforms_1f_;
  std::unordered_map<std::string, Uniform<int>> uniforms_1i_;
  std::unordered_map<std::string, Uniform<unsigned int>> uniforms_1ui_;
  std::unordered_map<std::string, Uniform<bool>> uniforms_1b_;
  std::unordered_map<std::string, Uniform<glm::vec3>> uniforms_3f_;
  std::unordered_map<std::string, Uniform<glm::vec4>> uniforms_4f_;
  std::unordered_map<std::string, Uniform<glm::mat3>> uniforms_3x3_;
  std::unordered_map<std::string, Uniform<glm::mat4>> uniforms_4x4_;

  std::unordered_map<std::string, const Texture*> textures_;
  std::unordered_map<std::string, const CubeTexture*> cube_textures_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_MATERIAL_MATERIAL_H
