#include "presenter/canvaspresenter.h"

#include <memory>

CanvasPresenter::CanvasPresenter(std::shared_ptr<Universe> universe,
                                 NVGcontext* context, Canvas* canvas)
    : Presenter(std::move(universe), context),
      canvas_(canvas),
      camera_controller_(
          get_universe()->get_camera_library().get_current_item()),
      last_update_time_(glfwGetTime()) {}

void CanvasPresenter::Init() {
  canvas_->start();
  Update();

  canvas_->get_mouse_move_signal().Connect([this](
                                               glm::vec2& displacement_vector) {
    std::shared_ptr<Scene> scene =
        get_universe()->get_scene_library().get_current_item();
    if (scene.get() != nullptr && scene->get_is_ready()) {
      float yaw_angle = displacement_vector.x * glm::pi<float>();
      float pitch_angle = displacement_vector.y * glm::pi<float>();
      get_universe()->get_camera_library().get_current_item()->Pitch(
          pitch_angle);
      get_universe()->get_camera_library().get_current_item()->Yaw(yaw_angle);
      get_universe()->get_camera_library().get_current_item()->Update();
    }
  });
}

void CanvasPresenter::Resize(unsigned int width, unsigned int height) {
  canvas_->Resize(width, height);
  camera_controller_.SetSize(width, height);
}

void CanvasPresenter::Update() {
  std::function<void()> drawCall = [&]() {
    double current_time = glfwGetTime();
    double delta_time = current_time - last_update_time_;
    last_update_time_ = current_time;

    camera_controller_.Update(delta_time);

    std::shared_ptr<Camera> camera =
        get_universe()->get_camera_library().get_current_item();
    camera->Update();

    std::shared_ptr<Scene> scene =
        get_universe()->get_scene_library().get_current_item();

    std::vector<std::shared_ptr<Light>> lights =
        get_universe()->get_light_library().get_items();
    if (scene.get() != nullptr && scene->get_is_ready()) {
      scene->Animate();
      scene->Update();
      scene->get_scene_tree()->DrawScene(
          camera->get_view_matrix(), camera->get_projection_matrix(), lights);
    }
  };

  canvas_->setDrawCall(drawCall);
}
