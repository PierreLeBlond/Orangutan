#ifndef ORANGUTAN_MANAGER_CANVAS_MANAGER_H
#define ORANGUTAN_MANAGER_CANVAS_MANAGER_H

#include <memory>

#include "camera/cameracontroller.h"
#include "presenter/presenter.h"
#include "ui/canvas.h"

namespace orangutan {

class CanvasManager {
 public:
  CanvasManager(Canvas* canvas, Camera* camera, Scene* scene);

  void Resize(unsigned int width, unsigned int height);

 private:
  Canvas* canvas_;

  Camera* camera_;
  CameraController camera_controller_;
  Scene* scene_;

  double last_update_time_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_PRESENTER_CANVAS_MANAGER_H
