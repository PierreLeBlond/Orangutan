#ifndef SCREEN_PRESENTER_H
#define SCREEN_PRESENTER_H

#include <memory>

#include "nanogui/screen.h"
#include "presenter/presenter.h"

class ScreenPresenter : public Presenter {
 public:
  ScreenPresenter(nanogui::Screen* screen, std::shared_ptr<Universe> universe);
  void Init() override;
  void Draw();
  void Update() override;

  [[nodiscard]] nanogui::Screen* get_screen() const;

 private:
  nanogui::Screen* screen_;
};

#endif  // SCREEN_PRESENTER_H
