#ifndef APP_H
#define APP_H

#include "view/screenview.h"

#include "presenter/screenpresenter.h"
#include "presenter/canvaspresenter.h"
#include "presenter/universepresenter.h"
#include "presenter/renderableobjectpresenter.h"

#include "model/universe.h"

#include "scene/scene.h"

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
    nanogui::ref<nanogui::Window>       _canvasWindow;

    std::shared_ptr<ScreenPresenter>            _screenPresenter;
    std::shared_ptr<CanvasPresenter>            _canvasPresenter;
    std::shared_ptr<UniversePresenter>          _universePresenter;
    std::shared_ptr<RenderableObjectPresenter>  _renderableObjectPresenter;

    std::shared_ptr<Universe>           _universe;
    std::shared_ptr<Scene>              _scene;
};

#endif //APP_H
