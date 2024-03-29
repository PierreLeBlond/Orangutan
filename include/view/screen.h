#ifndef ORANGUTAN_VIEW_SCREEN_H
#define ORANGUTAN_VIEW_SCREEN_H

#include <nanogui/screen.h>

namespace orangutan {

class Screen : public nanogui::Screen {
 public:
  Screen(GLFWwindow* window);

  bool keyboard_event(int key, int scancode, int action,
                      int modifiers) override;
};

}  // namespace orangutan

#endif  // ORANGUTAN_VIEW_SCREEN_H
