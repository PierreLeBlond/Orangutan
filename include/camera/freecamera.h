#ifndef ORANGUTAN_CAMERA_FREE_CAMERA_H
#define ORANGUTAN_CAMERA_FREE_CAMERA_H

#include "camera/camera.h"

namespace orangutan {

class FreeCamera : public Camera {
 public:
  FreeCamera(const std::string &name);

  void Update() override;
  void Move(glm::vec3 &direction) override;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CAMERA_FREE_CAMERA_H
