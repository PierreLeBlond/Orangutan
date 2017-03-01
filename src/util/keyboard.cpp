#include "util/keyboard.h"

#include <iostream>

Keyboard Keyboard::_instance;

Keyboard::Keyboard()
{
    _keyboard.resize(348, KEYUP);
}

Keyboard& Keyboard::instance()
{
    return _instance;
}

const std::vector<State>& Keyboard::getKeyboard() const
{
    return _keyboard;
}

void Keyboard::setState(int key, State state)
{
    if(key > -1 && key < 349)
            _keyboard[key] = state;
    else
        std::cout << "Unknow key" << std::endl;
}

State Keyboard::getState(int key) const
{
    if(key > -1 && key < 349)
        return _keyboard[key];
    else
        return KEYUNKNOW;
}
