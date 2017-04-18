#include "presenter/screenpresenter.h"

ScreenPresenter::ScreenPresenter(std::shared_ptr<Presenter> parent) :
    Presenter(parent)
{}

void ScreenPresenter::init()
{
    _screenView->drawAll();
    _screenView->setVisible(true);

    _screenView->performLayout();
}

void ScreenPresenter::update()
{
    for(auto &childPresenter : _childPresenters)
    {
        childPresenter->update();
    }

    _screenView->performLayout();
}

void ScreenPresenter::notifyChangeToModel()
{
    update();
}

NVGcontext* ScreenPresenter::getContext()
{
    return _screenView->nvgContext();
}

void ScreenPresenter::setScreenView(nanogui::ref<ScreenView> screenView)
{
    _screenView = screenView;
}
