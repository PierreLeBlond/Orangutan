#ifndef ORANGUTAN_CAMERA_CAMERA_CONTROLLER_H
#define ORANGUTAN_CAMERA_CAMERA_CONTROLLER_H

#include <memory>

#include "camera/camera.h"

class CameraController {
 public:
  CameraController(std::shared_ptr<Camera> camera);

  void set_camera(std::shared_ptr<Camera> camera);
  void Update(double delta_time);

  void SetSize(unsigned int width, unsigned int height);

 private:
  std::shared_ptr<Camera> camera_;
  unsigned int width_;
  unsigned int height_;
};

#endif  // ORANGUTAN_CAMERA_CAMERA_CONTROLLER_H
