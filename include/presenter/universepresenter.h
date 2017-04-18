#ifndef UNIVERSE_PRESENTER_H
#define UNIVERSE_PRESENTER_H

#include "presenter/presenter.h"
#include "view/view.h"

class UniversePresenter : public Presenter
{
public:
                                                UniversePresenter(std::shared_ptr<Presenter> parent = nullptr);
    virtual void                                init();
    virtual void                                update();

    void                                        setView(nanogui::ref<View> view);

private:

    nanogui::ref<View>                          _view;
};

#endif // UNIVERSE_PRESENTER_H
