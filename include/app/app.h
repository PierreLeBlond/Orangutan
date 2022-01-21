#ifndef APP_H
#define APP_H

#include <memory>

#include "model/universe.h"
#include "presenter/canvaspresenter.h"
#include "presenter/renderableobjectpresenter.h"
#include "presenter/screenpresenter.h"
#include "presenter/universepresenter.h"
#include "scene/scene.h"
#include "view/screen.h"

class App {
 public:
  void Init(GLFWwindow* window);

  void Draw();
  void Resize(unsigned int width, unsigned int height);

  void BindEvents(GLFWwindow* window, orangutan::Screen* screen);
  void InitUniverse();

 private:
  std::shared_ptr<ScreenPresenter> _screenPresenter;
  std::shared_ptr<CanvasPresenter> _canvasPresenter;
  std::shared_ptr<UniversePresenter> _universePresenter;
  std::shared_ptr<RenderableObjectPresenter> _renderableObjectPresenter;

  std::shared_ptr<Universe> _universe;
  std::shared_ptr<Scene> _scene;
};

#endif  // APP_H
