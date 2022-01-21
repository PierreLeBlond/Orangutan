#include "view/screen.h"

#include <iostream>
#include <map>

#include "GLFW/glfw3.h"
#include "util//keyboard.h"

namespace orangutan {

const std::map<int, KeyState> kGlfwActionToKeyState = {
    {GLFW_PRESS, kPressed},
    {GLFW_RELEASE, kReleased},
    {GLFW_REPEAT, kPressed},
    {GLFW_KEY_UNKNOWN, kUnknow}};

Screen::Screen(GLFWwindow* window) : nanogui::Screen() {
  initialize(window, true);
}

bool Screen::keyboard_event(int key, int scancode, int action, int modifiers) {
  KeyState key_state = kGlfwActionToKeyState.at(action);
  Keyboard::instance().setState(key, key_state);
  return true;
}

}  // namespace orangutan
