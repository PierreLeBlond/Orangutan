#ifndef ORANGUTAN_PRESENTER_UNIVERSE_PRESENTER_H
#define ORANGUTAN_PRESENTER_UNIVERSE_PRESENTER_H

#include "presenter/presenter.h"
#include "ui/window.h"

namespace orangutan {

class UniversePresenter : public Presenter {
 public:
  UniversePresenter(Universe* universe, NVGcontext* context, Window* window);
  void Init() override;
  void Resize(unsigned int width, unsigned int height) override;
  void Update() override;

 private:
  Window* window_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_PRESENTER_UNIVERSE_PRESENTER_H
