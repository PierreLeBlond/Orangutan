#ifndef ORANGUTAN_MATERIAL_SHADERSTRATEGY_H
#define ORANGUTAN_MATERIAL_SHADERSTRATEGY_H

#include <algorithm>

#include "core/debug.h"
#include "core/shader/shaderwrapper.h"
#include "core/vertex/vao.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "material/material.h"
#include "object/light.h"

namespace orangutan {

class Material;
class ShaderProgram;

class ShaderStrategy : public Asset {
 public:
  ShaderStrategy(const std::string& name);

  template <class T>
  void SetUniform(const Uniform<T>& uniform) const {
    std::vector<std::string> names = shader_wrapper_->getUniformsName();
    shader_wrapper_->setUniform(uniform.getName(), uniform.getValue());
  }

  void SetUniforms(const Material& material, const glm::mat4& model_matrix,
                   const glm::mat4& view_matrix,
                   const glm::vec3& camera_position,
                   const glm::mat4& projection_matrix,
                   const std::vector<Light*>& lights, const Ibl& ibl,
                   const Texture& brdf) const;

  void SetLightUniforms(const std::vector<Light*>& lights,
                        const glm::mat4& view_matrix, const Ibl& ibl,
                        const Texture& brdf) const;
  void SetSceneUniforms(const glm::mat4& model_matrix,
                        const glm::mat4& view_matrix,
                        const glm::vec3& camera_position,
                        const glm::mat4& projection_matrix) const;
  void SetMaterialUniforms(const Material& material) const;

  void InitAttribute();

  void Draw(const Vao& vao) const;

  void set_shader_wrapper(ShaderWrapper* shader_wrapper);
  [[nodiscard]] ShaderWrapper& get_shader_wrapper() const;

  [[nodiscard]] int get_vertex_attribute() const { return vertex_attribute_; }
  [[nodiscard]] int get_normal_attribute() const { return normal_attribute_; }
  [[nodiscard]] int get_texture_coordinate_attribute() const {
    return texture_coordinate_attribute_;
  }

 private:
  ShaderWrapper* shader_wrapper_;
  unsigned int program_id_;

  int vertex_attribute_;
  int normal_attribute_;
  int texture_coordinate_attribute_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_MATERIAL_SHADERSTRATEGY_H
