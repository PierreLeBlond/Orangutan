#ifndef FREE_CAMERA_H
#define FREE_CAMERA_H

#include "camera/camera.h"

class FreeCamera : public Camera {
 public:
  FreeCamera(const std::string &name);

  void Update() override;
  void Move(glm::vec3 &direction) override;
};

#endif  // FREE_CAMERA_H
