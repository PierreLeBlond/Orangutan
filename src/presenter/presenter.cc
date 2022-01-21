#include "presenter/presenter.h"

#include <utility>

Presenter::Presenter(std::shared_ptr<Universe> universe, NVGcontext* context)
    : universe_(std::move(universe)), context_(context) {}

std::shared_ptr<Universe> Presenter::get_universe() const { return universe_; }

NVGcontext* Presenter::get_context() const { return context_; }

const std::vector<std::shared_ptr<Presenter>>& Presenter::get_child_presenters()
    const {
  return child_presenters_;
};

void Presenter::AddChildPresenter(std::shared_ptr<Presenter> child_presenter) {
  child_presenters_.push_back(child_presenter);
}
