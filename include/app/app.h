#ifndef ORANGUTAN_APP_APP_H
#define ORANGUTAN_APP_APP_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <memory>

#include "camera/camera.h"
#include "camera/cameracontroller.h"
#include "manager/texturemanager.h"
#include "model/universe.h"
#include "scene/scene.h"

namespace orangutan {

class App {
public:
  void Init();

  void Draw(int width, int height);

  void InitUniverse();

  [[nodiscard]] TextureManager *get_texture_manager() const;

private:
  std::unique_ptr<TextureManager> texture_manager_;

  std::unique_ptr<Universe> universe_;

  std::unique_ptr<Scene> scene_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<CameraController> camera_controller_;

  double last_update_time_;
};

} // namespace orangutan

#endif // ORANGUTAN_APP_APP_H
