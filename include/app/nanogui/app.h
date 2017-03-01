#ifndef APP_H
#define APP_H

#include "view/nanogui/screenview.h"
#include "view/nanogui/canvasview.h"

#include "model/universe.h"

#include "scene/scene.h"
#include "scene/renderer.h"

#include <nanogui/window.h>

#include <memory>

class App
{
public:

    void                                init();
    void                                initUniverse();
    void                                initScene();

private:

    nanogui::ref<ScreenView>            _screenView;
    nanogui::ref<CanvasView>            _canvasView;
    nanogui::ref<nanogui::Window>       _windowView;

    Universe                            _universe;

    std::shared_ptr<Scene>              _scene;
    std::unique_ptr<Renderer>           _renderer;

};

#endif //APP_H
