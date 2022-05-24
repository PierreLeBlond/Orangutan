#include "util/keyboard.h"

#include <iostream>
#include <memory>

namespace orangutan {

const int kNumberOfKeys = 348;

// Initialize static member
Keyboard Keyboard::_instance;

Keyboard::Keyboard() { _keyboard.resize(kNumberOfKeys, kReleased); }
Keyboard::~Keyboard() = default;

Keyboard& Keyboard::instance() { return _instance; }

const std::vector<KeyState>& Keyboard::getKeyboard() const { return _keyboard; }

void Keyboard::setState(int key, KeyState state) {
  if (key > -1 && key < kNumberOfKeys)
    _keyboard[key] = state;
  else
    std::cerr << "Unknow key" << std::endl;
}

KeyState Keyboard::getState(int key) const {
  if (key > -1 && key < kNumberOfKeys)
    return _keyboard[key];
  else
    return kUnknow;
}

}  // namespace orangutan
