#include "physics/transformable.h"

#include <chrono>
#include <iostream>

const glm::vec3 kNormalizedUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 kNormalizedRightVector = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 kNormalizedForwardVector = glm::vec3(0.0f, 0.0f, 1.0f);

Transform::Transform()
    : world_matrix_(1.0f),
      model_matrix_(1.0f),
      translation_matrix_(1.0f),
      x_scale_matrix_(1.0f),
      y_scale_matrix_(1.0f),
      z_scale_matrix_(1.0f),
      x_rotation_matrix_(1.0f),
      y_rotation_matrix_(1.0f),
      z_rotation_matrix_(1.0f),
      position_(1.0f) {}

const glm::mat4 &Transform::get_world_matrix() const { return world_matrix_; }
const glm::mat4 &Transform::get_model_matrix() const { return model_matrix_; }

const glm::vec4 Transform::GetDirection() const {
  return x_rotation_matrix_ * y_rotation_matrix_ * z_rotation_matrix_ *
         glm::vec4(kNormalizedForwardVector, 0.0f);
}

void Transform::SetParentMatrix(const glm::mat4 &parent_matrix) {
  world_matrix_ = parent_matrix * model_matrix_;
}

void Transform::set_model_matrix(const glm::mat4 &model_matrix) {
  model_matrix_ = model_matrix;
}

void Transform::SetXRotation(float angle) {
  x_rotation_matrix_ = glm::rotate(angle, kNormalizedRightVector);
  Update();
}

void Transform::SetYRotation(float angle) {
  y_rotation_matrix_ = glm::rotate(angle, kNormalizedUpVector);
  Update();
}

void Transform::SetZRotation(float angle) {
  z_rotation_matrix_ = glm::rotate(angle, kNormalizedForwardVector);
  Update();
}

void Transform::SetXScale(float scale) {
  x_scale_matrix_ = glm::scale(glm::vec3(scale, 1.0f, 1.0f));
  Update();
}

void Transform::SetYScale(float scale) {
  y_scale_matrix_ = glm::scale(glm::vec3(1.0f, scale, 1.0f));
  Update();
}

void Transform::SetZScale(float scale) {
  z_scale_matrix_ = glm::scale(glm::vec3(1.0f, 1.0f, scale));
  Update();
}

void Transform::SetXPos(float x) {
  position_.x = x;
  translation_matrix_ = glm::translate(position_);
  Update();
}

void Transform::SetYPos(float y) {
  position_.y = y;
  translation_matrix_ = glm::translate(position_);
  Update();
}

void Transform::SetZPos(float z) {
  position_.z = z;
  translation_matrix_ = glm::translate(position_);
  Update();
}

void Transform::set_position(const glm::vec3 &position) {
  position_ = position;
  translation_matrix_ = glm::translate(position_);
  Update();
}

void Transform::Move(glm::vec3 &direction) {
  position_ += direction;
  translation_matrix_ = glm::translate(position_);
  Update();
}

void Transform::Animate() {}

void Transform::Update() {
  model_matrix_ = translation_matrix_ * x_rotation_matrix_ *
                  y_rotation_matrix_ * z_rotation_matrix_ * x_scale_matrix_ *
                  y_scale_matrix_ * z_scale_matrix_;
}

