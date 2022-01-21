#ifndef CANVAS_PRESENTER_H
#define CANVAS_PRESENTER_H

#include <memory>

#include "camera/cameracontroller.h"
#include "presenter/presenter.h"
#include "view/canvas.h"

class CanvasPresenter : public Presenter {
 public:
  CanvasPresenter(std::shared_ptr<Universe> universe, NVGcontext* context,
                  Canvas* canvas);

  void Init() override;
  void Resize(unsigned int width, unsigned int height);
  void Update() override;

 private:
  Canvas* canvas_;

  CameraController camera_controller_;

  double last_update_time_;
};

#endif  // CANVAS_PRESENTER_H
