#include "presenter/universepresenter.h"

namespace orangutan {

UniversePresenter::UniversePresenter(Universe* universe, NVGcontext* context,
                                     Window* window)
    : Presenter(universe, context), window_(window) {}

void UniversePresenter::Init() {
  window_->set_layout(new nanogui::GroupLayout());

  Update();
}

void UniversePresenter::Resize(unsigned int width, unsigned int height) {
  window_->Resize(width, height);
}

void UniversePresenter::Update() { window_->clear(); }

}  // namespace orangutan
