#ifndef ORANGUTAN_PRESENTER_SCREEN_PRESENTER_H
#define ORANGUTAN_PRESENTER_SCREEN_PRESENTER_H

#include <memory>

#include "nanogui/screen.h"
#include "patterns/observer/signal.h"
#include "presenter/presenter.h"

namespace orangutan {

class ScreenPresenter : public Presenter {
 public:
  ScreenPresenter(nanogui::Screen* screen, Universe* universe);
  void Init() override;
  void Draw();
  void Resize(unsigned int width, unsigned int height) override;
  void Update() override;

  [[nodiscard]] nanogui::Screen* get_screen() const;

  void ConnectToResizeSignal(
      std::function<void(unsigned int, unsigned int)> handler);

 private:
  nanogui::Screen* screen_;

  Signal<unsigned int, unsigned int> resize_signal_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_PRESENTER_SCREEN_PRESENTER_H
