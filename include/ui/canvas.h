#ifndef ORANGUTAN_UI_CANVAS_H
#define ORANGUTAN_UI_CANVAS_H

#include <nanogui/canvas.h>
#include <nanogui/opengl.h>

#include <glm/glm.hpp>

#include "nanogui/vector.h"
#include "patterns/observer/signal.h"

namespace orangutan {

class Canvas : public nanogui::Canvas {
 public:
  Canvas(nanogui::Widget *parent);

  void start();
  void stop();

  void Resize(unsigned int width, unsigned int height);

  void setDrawCall(const std::function<void()> &drawcall);

  [[nodiscard]] Signal<glm::vec2 &> &get_mouse_move_signal();
  [[nodiscard]] Signal<> &get_after_draw_signal();

  void ConnectToAfterDrawSignal(const std::function<void()> &handler);
  void DisconnectToAfterDrawSignal(const std::function<void()> &handler);

  void draw_contents() override;

  bool mouse_motion_event(const nanogui::Vector2i &p,
                          const nanogui::Vector2i &rel, int button,
                          int modifiers) override;

  bool mouse_button_event(const nanogui::Vector2i &p, int button, bool down,
                          int modifiers) override;

 private:
  bool _draw;
  nanogui::Vector2i _lastMousePosition;
  bool _mouseIsPressed;

  std::function<void()> _drawCall;
  Signal<glm::vec2 &> mouse_move_signal_;
  Signal<> after_draw_signal_;
};

}  // namespace orangutan

#endif  // ORANGUTAN_UI_CANVAS_H
