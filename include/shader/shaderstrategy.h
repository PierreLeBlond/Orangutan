#ifndef SHADERSTRATEGY_H
#define SHADERSTRATEGY_H

#include <algorithm>

#include "core/debug.h"
#include "core/shader/shaderwrapper.h"
#include "core/vertex/vao.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "object/light.h"
#include "object/material.h"

class Material;
class ShaderProgram;

class ShaderStrategy : public Asset {
 public:
  ShaderStrategy(const std::string& name);

  template <class T>
  void SetUniform(const Uniform<T>& uniform) const {
    std::vector<std::string> names = shader_wrapper_->getUniformsName();
    auto it = std::find(names.begin(), names.end(), uniform.getName());
    if (it != names.end()) {
      shader_wrapper_->setUniform(uniform.getName(), uniform.getValue());
    }
  }

  void SetUniforms(const Material& material, const glm::mat4& model_matrix,
                   const glm::mat4& view_matrix,
                   const glm::mat4& projection_matrix,
                   const std::vector<std::shared_ptr<Light>>& lights) const;

  void SetLightUniforms(const std::vector<std::shared_ptr<Light>>& lights,
                        const glm::mat4& view_matrix) const;
  void SetMatrixUniforms(const glm::mat4& model_matrix,
                         const glm::mat4& view_matrix,
                         const glm::mat4& projection_matrix) const;
  void SetMaterialUniforms(const Material& material) const;

  void InitAttribute();

  void Draw(const Vao& vao) const;

  void set_shader_wrapper(std::shared_ptr<ShaderWrapper> shader_wrapper);
  [[nodiscard]] const std::shared_ptr<ShaderWrapper>& get_shader_wrapper()
      const;

  [[nodiscard]] int get_vertex_attribute() const { return vertex_attribute_; }
  [[nodiscard]] int get_normal_attribute() const { return normal_attribute_; }
  [[nodiscard]] int get_texture_coordinate_attribute() const {
    return texture_coordinate_attribute_;
  }

 private:
  std::shared_ptr<ShaderWrapper> shader_wrapper_;
  unsigned int program_id_;

  int vertex_attribute_;
  int normal_attribute_;
  int texture_coordinate_attribute_;
};

#endif  // SHADERSTRATEGY_H
