#include "presenter/presenter.h"

Presenter::Presenter(std::shared_ptr<Presenter> parent) :
    _parentPresenter(parent)
{
}

void Presenter::setUniverse(std::shared_ptr<Universe> universe)
{
    _universe = universe;
}

void Presenter::notifyChangeToModel()
{
    if(nullptr != _parentPresenter)
        _parentPresenter->notifyChangeToModel();
}

void Presenter::addChildPresenter(std::shared_ptr<Presenter> childPresenter)
{
    _childPresenters.push_back(childPresenter);
}

NVGcontext* Presenter::getContext()
{
    if(_parentPresenter != nullptr)
        return _parentPresenter->getContext();
    else
        return nullptr;
}
