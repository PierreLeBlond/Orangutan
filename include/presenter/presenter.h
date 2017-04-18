#ifndef PRESENTER_H
#define PRESENTER_H

#include "model/universe.h"

#include <memory>
#include <vector>

class Presenter
{
  public:
                                                Presenter(std::shared_ptr<Presenter> parent = nullptr);

    virtual void                                init() = 0;

    virtual void                                update() = 0;

    virtual void                                notifyChangeToModel();

    virtual NVGcontext*                         getContext();

    void                                        setUniverse(std::shared_ptr<Universe> universe);

    void                                        addChildPresenter(std::shared_ptr<Presenter> childPresenter);

  protected:
    std::shared_ptr<Universe>                   _universe;

    std::shared_ptr<Presenter>                  _parentPresenter;
    std::vector<std::shared_ptr<Presenter>>     _childPresenters;
};

#endif // PRESENTER_H
