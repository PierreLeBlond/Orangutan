#include "manager/canvasmanager.h"

#include <memory>
#include <new>

namespace orangutan {

CanvasManager::CanvasManager(Canvas* canvas, Camera* camera, Scene* scene)
    : canvas_(canvas),
      camera_(camera),
      camera_controller_(camera_),
      scene_(scene),
      last_update_time_(glfwGetTime()) {
  canvas_->get_mouse_move_signal().Connect([&](glm::vec2& displacement_vector) {
    float yaw_angle = displacement_vector.x * glm::pi<float>();
    float pitch_angle = displacement_vector.y * glm::pi<float>();
    camera_->Pitch(pitch_angle);
    camera_->Yaw(yaw_angle);
    camera_->Update();
  });

  std::function<void()> drawCall = [&]() {
    double current_time = glfwGetTime();
    double delta_time = current_time - last_update_time_;
    last_update_time_ = current_time;

    camera_controller_.Update(delta_time);
    camera_->Update();

    scene_->Animate();
    scene_->Update();
    scene_->Draw(camera_->get_view_matrix(),
                 camera_->get_transform().get_position(),
                 camera_->get_projection_matrix());
  };

  canvas_->setDrawCall(drawCall);

  canvas_->start();
}

void CanvasManager::Resize(unsigned int width, unsigned int height) {
  canvas_->Resize(width, height);
  camera_controller_.SetSize(width, height);
}

}  // namespace orangutan
