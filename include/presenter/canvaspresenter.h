#ifndef CANVAS_PRESENTER_H
#define CANVAS_PRESENTER_H

#include "presenter/presenter.h"
#include "view/canvasview.h"

#include "scene/renderer.h"

class CanvasPresenter : public Presenter
{
public:
                                                CanvasPresenter(std::shared_ptr<Presenter> parent = nullptr);

    virtual void                                init();
    virtual void                                update();

    void                                        setCanvasView(nanogui::ref<CanvasView> canvasView);

private:

    nanogui::ref<CanvasView>                    _canvasView;
    std::unique_ptr<Renderer>                   _renderer;
};

#endif // CANVAS_PRESENTER_H
