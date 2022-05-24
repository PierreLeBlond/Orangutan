#ifndef ORANGUTAN_CAMERA_CAMERA_CONTROLLER_H
#define ORANGUTAN_CAMERA_CAMERA_CONTROLLER_H

#include <memory>

#include "camera/camera.h"

namespace orangutan {

class CameraController {
 public:
  CameraController(Camera* camera);

  void set_camera(Camera* camera);
  void Update(double delta_time);

  void SetSize(unsigned int width, unsigned int height);

 private:
  Camera* camera_;
  unsigned int width_;
  unsigned int height_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CAMERA_CAMERA_CONTROLLER_H
