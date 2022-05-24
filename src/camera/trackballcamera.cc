#include "camera/trackballcamera.h"

#include <iostream>

#include "glm/gtx/string_cast.hpp"

namespace orangutan {

const float kDefaultRadius = 10.0f;
const float kNear = 0.001f;
const float kFar = 1000.0f;

TrackBallCamera::TrackBallCamera(const std::string &name)
    : Camera(name), _radius(kDefaultRadius) {}

void TrackBallCamera::Update() {
  const float fovy = get_fovy();
  const float aspect_ratio = get_aspect_ratio();
  set_position(get_focus_point() + _radius * get_roll());
  set_view_matrix(glm::lookAt(get_transform().get_position(), get_focus_point(),
                              get_yaw()));
  set_projection_matrix(glm::perspective(fovy, aspect_ratio, kNear, kFar));
  set_model_matrix(glm::inverse(get_view_matrix()));
}

void TrackBallCamera::Move(glm::vec3 &direction) {
  const float speed = get_speed();
}

}  // namespace orangutan
