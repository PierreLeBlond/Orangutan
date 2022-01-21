#include "camera/freecamera.h"

#include <iostream>

#include "glm/gtx/string_cast.hpp"

const float kNear = 0.001f;
const float kFar = 1000.0f;

FreeCamera::FreeCamera(const std::string& name) : Camera(name) {}

void FreeCamera::Update() {
  const float fovy = get_fovy();
  const float aspect_ratio = get_aspect_ratio();
  set_view_matrix(glm::lookAt(get_transform().get_position(),
                              get_transform().get_position() - get_roll(),
                              get_yaw()));
  set_projection_matrix(
      glm::perspective(glm::radians(fovy), aspect_ratio, kNear, kFar));
  set_model_matrix(glm::inverse(get_view_matrix()));
}

void FreeCamera::Move(glm::vec3& direction) {
  const float speed = get_speed();
  glm::vec3 camera_direction = glm::vec3(get_transform().get_model_matrix() *
                                         glm::vec4(direction, 0.0f));
  glm::vec3 scaled_camera_direction = speed * camera_direction;
  ObjectNode::Move(scaled_camera_direction);
}
