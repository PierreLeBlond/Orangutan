#include "presenter/canvaspresenter.h"

CanvasPresenter::CanvasPresenter(std::shared_ptr<Presenter> parent) :
    Presenter(parent)
{}

void CanvasPresenter::init()
{
    if(_canvasView.get() != nullptr)
        _canvasView->start();
    _renderer = std::make_unique<Renderer>();
    update();
}

void CanvasPresenter::update()
{
    std::function<void()> drawCall = [&](){
        std::shared_ptr<Scene> scene = _universe->getSceneLibrary().getCurrentItem();
        if(scene.get() != nullptr && scene->isReady())
        {
            scene->animate();
            scene->update();
            _renderer->draw(*scene);
        }
    };

    _canvasView->setDrawCall(drawCall);
}

void CanvasPresenter::setCanvasView(nanogui::ref<CanvasView> canvasView)
{
    _canvasView = canvasView;
}
