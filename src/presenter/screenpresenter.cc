#include "presenter/screenpresenter.h"

#include <memory>

ScreenPresenter::ScreenPresenter(nanogui::Screen* screen,
                                 std::shared_ptr<Universe> universe)
    : Presenter(std::move(universe), screen->nvg_context()), screen_(screen) {}

void ScreenPresenter::Init() {
  screen_->set_visible(true);
  screen_->perform_layout();
  screen_->clear();
  screen_->draw_all();
}

void ScreenPresenter::Draw() {
  screen_->draw_setup();
  screen_->clear();  // glClear
  screen_->draw_contents();
  screen_->draw_widgets();
  screen_->draw_teardown();
}

void ScreenPresenter::Update() {
  for (auto& childPresenter : get_child_presenters()) {
    childPresenter->Update();
  }

  screen_->perform_layout();
}

nanogui::Screen* ScreenPresenter::get_screen() const { return screen_; }
