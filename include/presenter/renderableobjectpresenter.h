#ifndef RENDERABLE_OBJECT_PRESENTER_H
#define RENDERABLE_OBJECT_PRESENTER_H

#include "presenter/presenter.h"
#include "view/view.h"

class RenderableObjectPresenter : public Presenter
{
public:
                                                RenderableObjectPresenter(std::shared_ptr<Presenter> parent = nullptr);
    virtual void                                init();
    virtual void                                update();

    void                                        setView(nanogui::ref<View> view);

    void                                        updateMaterial(const Material &material,
                                                               const std::vector<std::string> &names);

private:

    nanogui::ref<View>                          _view;
};

#endif // RENDERABLE_OBJECT_PRESENTER_H
