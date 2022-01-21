#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "util/util.h"

class Transformable {
 public:
  virtual void SetParentMatrix(const glm::mat4& parentMatrix) = 0;
  virtual void set_model_matrix(const glm::mat4& modelMatrix) = 0;

  virtual void SetXRotation(float angle) = 0;
  virtual void SetYRotation(float angle) = 0;
  virtual void SetZRotation(float angle) = 0;

  virtual void SetXScale(float scale) = 0;
  virtual void SetYScale(float scale) = 0;
  virtual void SetZScale(float scale) = 0;

  virtual void set_position(const glm::vec3& position) = 0;

  virtual void SetXPos(float x) = 0;
  virtual void SetYPos(float y) = 0;
  virtual void SetZPos(float z) = 0;

  virtual void Move(glm::vec3& direction) = 0;
  virtual void Animate() = 0;
  virtual void Update() = 0;
};

class Transform : public Transformable {
 public:
  Transform();

  [[nodiscard]] const glm::mat4& get_world_matrix() const;
  [[nodiscard]] const glm::mat4& get_model_matrix() const;

  [[nodiscard]] inline float GetXPos() const { return position_.x; }
  [[nodiscard]] inline float GetYPos() const { return position_.y; }
  [[nodiscard]] inline float GetZPos() const { return position_.z; }

  [[nodiscard]] inline glm::vec3 get_position() const { return position_; }
  [[nodiscard]] inline glm::vec3 GetGlobalPos() const {
    return glm::vec3(world_matrix_[3][0], world_matrix_[3][1],
                     world_matrix_[3][2]);
  }

  [[nodiscard]] const glm::vec4 GetDirection() const;

  // inherit from transformable
  void SetParentMatrix(const glm::mat4& parent_matrix) override;
  void set_model_matrix(const glm::mat4& model_matrix) override;

  void SetXRotation(float angle) override;
  void SetYRotation(float angle) override;
  void SetZRotation(float angle) override;

  void SetXScale(float scale) override;
  void SetYScale(float scale) override;
  void SetZScale(float scale) override;

  void SetXPos(float x) override;
  void SetYPos(float y) override;
  void SetZPos(float z) override;

  void set_position(const glm::vec3& position) override;

  void Move(glm::vec3& direction) override;
  void Animate() override;
  void Update() override;

 private:
  glm::mat4 world_matrix_;
  glm::mat4 model_matrix_;
  glm::mat4 translation_matrix_;
  glm::mat4 x_scale_matrix_;
  glm::mat4 y_scale_matrix_;
  glm::mat4 z_scale_matrix_;
  glm::mat4 x_rotation_matrix_;
  glm::mat4 y_rotation_matrix_;
  glm::mat4 z_rotation_matrix_;

  glm::vec3 position_;
};

#endif  // TRANSFORMABLE_H
