#include "presenter/screenpresenter.h"

#include <memory>

#include "nanogui/vector.h"

namespace orangutan {

ScreenPresenter::ScreenPresenter(nanogui::Screen* screen, Universe* universe)
    : Presenter(universe, screen->nvg_context()), screen_(screen) {}

void ScreenPresenter::Init() {
  screen_->set_visible(true);
  screen_->perform_layout();
  screen_->clear();
  screen_->draw_all();

  screen_->set_resize_callback(
      [&](nanogui::Vector2i size) { Resize(size.x(), size.y()); });
}

void ScreenPresenter::Draw() {
  screen_->draw_setup();
  screen_->clear();  // glClear
  screen_->draw_contents();
  screen_->draw_widgets();
  screen_->draw_teardown();
}

void ScreenPresenter::Resize(unsigned int width, unsigned int height) {
  for (auto& childPresenter : get_child_presenters()) {
    childPresenter->Resize(width, height);
  }

  resize_signal_.Emit("", width, height);

  screen_->perform_layout();
}

void ScreenPresenter::Update() {
  for (auto& childPresenter : get_child_presenters()) {
    childPresenter->Update();
  }

  screen_->perform_layout();
}

void ScreenPresenter::ConnectToResizeSignal(
    std::function<void(unsigned int, unsigned int)> handler) {
  resize_signal_.Connect(handler);
}

nanogui::Screen* ScreenPresenter::get_screen() const { return screen_; }

}  // namespace orangutan
