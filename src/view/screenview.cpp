#include "view/screenview.h"
#include "core/debug.h"

#include <nanogui/window.h>
#include <nanogui/layout.h>

#include <chrono>

ScreenView::ScreenView(int width, int height, const std::string& name) :
    nanogui::Screen(Eigen::Vector2i(width, height), name)
{
}

bool ScreenView::keyboardEvent(int key, int scancode, int action, int modifiers)
{
    bool catched;
    if (!(catched = (nanogui::Screen::keyboardEvent(key, scancode, action, modifiers))))
    {
        if(action == GLFW_PRESS)
        {
            switch(key)
            {
              case GLFW_KEY_ESCAPE:
                setVisible(false);
                catched = true;
                break;
              default:
                Keyboard::instance().setState(key, KEYDOWN);
                catched = false;
                break;
            }
        }
        else if(action == GLFW_RELEASE)
        {
            Keyboard::instance().setState(key, KEYUP);
            catched = true;
        }
    }
    return catched;
}

