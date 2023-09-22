#include "ui/canvas.h"

#include <iostream>

namespace orangutan {

const float kRedBackgroundComponent = 0.3f;
const float kBlueBackgroundComponent = 0.56f;

Canvas::Canvas(nanogui::Widget *parent)
    : nanogui::Canvas(parent),
      _draw(false),
      _mouseIsPressed(false),
      _drawCall([]() {}),
      mouse_move_signal_() {
  // nanogui::Color color(kRedBackgroundComponent, 0.0f,
  // kBlueBackgroundComponent,
  nanogui::Color color(1.0f, 1.0f, 1.0f, 1.0f);

  set_background_color(color);
  set_draw_border(true);
}

void Canvas::start() { _draw = true; }

void Canvas::stop() { _draw = false; }

void Canvas::Resize(unsigned int width, unsigned int height) {
  set_size(nanogui::Vector2i(width, height));
}

void Canvas::setDrawCall(const std::function<void()> &drawcall) {
  _drawCall = drawcall;
}

Signal<glm::vec2 &> &Canvas::get_mouse_move_signal() {
  return mouse_move_signal_;
}

Signal<> &Canvas::get_after_draw_signal() { return after_draw_signal_; }

void Canvas::draw_contents() {
  if (_draw) {
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_BLEND);

    glDisable(GL_CULL_FACE);

    // For sky box to render properly
    glDepthFunc(GL_LEQUAL);

    _drawCall();

    after_draw_signal_.Emit("");
  }
}

bool Canvas::mouse_motion_event(const nanogui::Vector2i &p,
                                const nanogui::Vector2i &rel, int button,
                                int modifiers) {
  if (_mouseIsPressed) {
    nanogui::Vector2i newMousePosition = p;
    nanogui::Vector2i mouse_displacement_vector =
        newMousePosition - _lastMousePosition;
    glm::vec2 displacement_vector =
        glm::vec2((float)mouse_displacement_vector.x() / (float)width(),
                  (float)mouse_displacement_vector.y() / (float)height());
    mouse_move_signal_.Emit("", displacement_vector);
    _lastMousePosition = p;
  }

  return true;
}

bool Canvas::mouse_button_event(const nanogui::Vector2i &p, int button,
                                bool down, int modifiers) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (down) {
      _lastMousePosition = p;
      _mouseIsPressed = true;
    } else {
      _mouseIsPressed = false;
    }
  }
  return true;
}

}  // namespace orangutan

