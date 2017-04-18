#ifndef SCREEN_PRESENTER_H
#define SCREEN_PRESENTER_H

#include "presenter/presenter.h"
#include "view/screenview.h"

class ScreenPresenter : public Presenter
{
public:
                                                ScreenPresenter(std::shared_ptr<Presenter> parent = nullptr);
    virtual void                                init();
    virtual void                                update();

    virtual void                                notifyChangeToModel();
    virtual NVGcontext*                         getContext();

    void                                        setScreenView(nanogui::ref<ScreenView> screenView);

private:

    nanogui::ref<ScreenView>                    _screenView;
};

#endif // SCREEN_PRESENTER_H
