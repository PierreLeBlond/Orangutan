#include "camera/camera.h"

#include <cmath>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

#include "glm/gtx/string_cast.hpp"

namespace orangutan {

const float kDefaultFovy = 75.0f;
const float kMinFovy = 10.0f;
const float kMaxFovy = 100.0f;

const float kHalfCircleAngle = 180.0f;

const glm::vec3 kDefaultYaw = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 kDefaultPitch = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 kDefaultRoll = glm::vec3(0.0f, 0.0f, 1.0f);

Camera::Camera(const std::string& name)
    : ObjectNode(name),
      fovy_(kDefaultFovy),
      aspect_ratio_(1.0f),
      view_matrix_(glm::mat4(0.0f)),
      projection_matrix_(glm::mat4(0.0f)),
      focus_point_(glm::vec3(0.0f, 0.0f, 0.0f)),
      yaw_angle_(0.0f),
      pitch_angle_(0.0f),
      roll_angle_(0.0f),
      yaw_(kDefaultYaw),
      pitch_(kDefaultPitch),
      roll_(kDefaultRoll),
      speed_(1.0f) {
  // Focus();
  UpdateYawPitchRoll();
}

const glm::mat4& Camera::get_view_matrix() const { return view_matrix_; }
void Camera::set_view_matrix(const glm::mat4& view_matrix) {
  view_matrix_ = view_matrix;
}

const glm::mat4& Camera::get_projection_matrix() const {
  return projection_matrix_;
}
void Camera::set_projection_matrix(const glm::mat4& projection_matrix) {
  projection_matrix_ = projection_matrix;
}

const glm::vec3& Camera::get_focus_point() const { return focus_point_; }
void Camera::set_focus_point(const glm::vec3& focus_point) {
  focus_point_ = focus_point;
}
void Camera::set_focus_object(std::shared_ptr<Object> focus_object) {
  focus_object_ = focus_object;
}
void Camera::UpdateFocus() {
  if (focus_object_ != nullptr) {
    focus_point_ = focus_object_->getTransform().get_position();
  }
}

const float Camera::get_fovy() const { return fovy_; }
void Camera::set_fovy(float fovy) {
  if (fovy > kMaxFovy || fovy < kMinFovy) {
    std::cerr << "Camera::setFovy : value should be between " << kMinFovy
              << " and " << kMaxFovy << ", but is " << fovy << std::endl;
    return;
  }
  fovy_ = fovy;
}

const float Camera::get_aspect_ratio() const { return aspect_ratio_; }
void Camera::set_aspect_ratio(float aspect_ratio) {
  aspect_ratio_ = aspect_ratio;
}

const float Camera::get_speed() const { return speed_; }
void Camera::set_speed(float speed) { speed_ = speed; }

void Camera::Focus() {
  view_matrix_ = glm::lookAt(get_transform().get_position(),
                             get_transform().get_position() + roll_, yaw_);
  glm::vec4 focus = view_matrix_ * glm::vec4(focus_point_, 1.0f);
  focus_point_ = glm::vec3(focus);

  glm::vec3 yawFocusPoint(focus_point_.x, 0.0f, focus_point_.z);
  yawFocusPoint = glm::normalize(yawFocusPoint);

  float yawAngle =
      glm::acos(glm::dot(yawFocusPoint, glm::vec3(0.0f, 0.0f, -1.0f)));
  yawAngle = (yawAngle * kHalfCircleAngle) / glm::pi<float>();

  Yaw(yawAngle);

  glm::vec3 pitchFocusPoint(0.0f, focus_point_.y, focus_point_.z);
  pitchFocusPoint = glm::normalize(pitchFocusPoint);

  float pitchAngle =
      glm::acos(glm::dot(pitchFocusPoint, glm::vec3(0.0f, 0.0f, -1.0f)));
  pitchAngle = (pitchAngle * kHalfCircleAngle) / glm::pi<float>();

  Pitch(pitchAngle);
}

void Camera::UpdateYawPitchRoll() {
  glm::mat4 pitchMatrix = glm::rotate(pitch_angle_, kDefaultPitch);
  glm::mat4 yawMatrix = glm::rotate(yaw_angle_, kDefaultYaw);
  glm::mat4 rollMatrix = glm::rotate(roll_angle_, kDefaultRoll);

  roll_ = glm::vec3(rollMatrix * yawMatrix * pitchMatrix *
                    glm::vec4(kDefaultRoll, 0.0f));
  yaw_ = glm::vec3(rollMatrix * yawMatrix * pitchMatrix *
                   glm::vec4(kDefaultYaw, 0.0f));

  pitch_ = glm::cross(yaw_, roll_);

  // std::cout << "roll_angle: " << roll_angle_ << std::endl;
  // std::cout << "yaw_angle: " << yaw_angle_ << std::endl;
  // std::cout << "pitch_angle: " << pitch_angle_ << std::endl;

  // std::cout << "roll: " << roll_.x << " " << roll_.y << " " << roll_.z
  // << std::endl;
  // std::cout << "yaw: " << yaw_.x << " " << yaw_.y << " " << yaw_.z <<
  // std::endl; std::cout << "pitch: " << pitch_.x << " " << pitch_.y << " " <<
  // pitch_.z
  // << std::endl;
}

const glm::vec3& Camera::get_pitch() const { return pitch_; }
void Camera::Pitch(float pitch_angle) {
  pitch_angle_ = pitch_angle_ + pitch_angle;
  pitch_angle_ =
      glm::clamp(pitch_angle_, -glm::half_pi<float>(), glm::half_pi<float>());
  pitch_angle_ = fmod(pitch_angle_, 2.0f * glm::pi<float>());
  UpdateYawPitchRoll();
}

const glm::vec3& Camera::get_yaw() const { return yaw_; }
void Camera::Yaw(float yawAngle) {
  yaw_angle_ = fmod(yaw_angle_ + yawAngle, 2.0f * glm::pi<float>());
  UpdateYawPitchRoll();
}

const glm::vec3& Camera::get_roll() const { return roll_; }
void Camera::Roll(float rollAngle) {
  roll_angle_ = fmod(roll_angle_ + rollAngle, 2.0f * glm::pi<float>());
  UpdateYawPitchRoll();
}

}  // namespace orangutan
