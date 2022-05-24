#include "presenter/presenter.h"

#include <utility>

namespace orangutan {

Presenter::Presenter(Universe* universe, NVGcontext* context)
    : universe_(universe), context_(context) {}

Universe& Presenter::get_universe() const { return *universe_; }

NVGcontext* Presenter::get_context() const { return context_; }

const std::vector<Presenter*>& Presenter::get_child_presenters() const {
  return child_presenters_;
};

void Presenter::AddChildPresenter(Presenter& child_presenter) {
  child_presenters_.push_back(&child_presenter);
}

}  // namespace orangutan
