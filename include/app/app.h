#ifndef ORANGUTAN_APP_APP_H
#define ORANGUTAN_APP_APP_H

#include <memory>

#include "manager/canvasmanager.h"
#include "manager/texturemanager.h"
#include "model/universe.h"
#include "presenter/screenpresenter.h"
#include "presenter/universepresenter.h"
#include "scene/scene.h"
#include "ui/screen.h"
#include "ui/texturewindow.h"

namespace orangutan {

class App {
 public:
  void Init(GLFWwindow* window);

  void Draw();

  void BindEvents(GLFWwindow* window, Screen* screen);
  void InitUniverse();

 private:
  std::unique_ptr<ScreenPresenter> screen_presenter_;
  std::unique_ptr<CanvasManager> canvas_manager_;

  std::unique_ptr<TextureManager> texture_manager_;
  TextureWindow* texture_window_;

  std::unique_ptr<UniversePresenter> universe_presenter_;

  std::unique_ptr<Universe> universe_;
  std::unique_ptr<Scene> scene_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_APP_APP_H
