#ifndef CANVAS_H
#define CANVAS_H

#include <nanogui/canvas.h>
#include <nanogui/opengl.h>

#include <glm/glm.hpp>

#include "nanogui/vector.h"
#include "patterns/observer/signal.h"

class Canvas : public nanogui::Canvas {
 public:
  Canvas(nanogui::Widget *parent);

  void start();
  void stop();

  void Resize(unsigned int width, unsigned int height);

  void setDrawCall(const std::function<void()> &drawcall);

  [[nodiscard]] Signal<glm::vec2 &> &get_mouse_move_signal();

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
};

#endif  // CANVAS_H
