#ifndef UNIVERSE_PRESENTER_H
#define UNIVERSE_PRESENTER_H

#include "presenter/presenter.h"
#include "view/view.h"

class UniversePresenter : public Presenter {
 public:
  UniversePresenter(std::shared_ptr<Universe> universe, NVGcontext* context,
                    View* view);
  void Init() override;
  void Update() override;

 private:
  View* view_;
};

#endif  // UNIVERSE_PRESENTER_H
