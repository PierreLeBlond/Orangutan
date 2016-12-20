#include "app/nanogui/screen.h"
#include "core/debug.h"

#include <nanogui/window.h>
#include <nanogui/layout.h>

Screen::Screen(int width, int height, std::string name, bool b) :
    nanogui::Screen(Eigen::Vector2i(width, height), name, b)
{
    nanogui::Window *window = new nanogui::Window(this, "Canvas");
    window->setPosition(Eigen::Vector2i(15, 15));
    window->setLayout(new nanogui::GroupLayout());

    _canvas = new Canvas(window);
    _canvas->resize(800, 600);

    performLayout();
}

Screen::~Screen()
{
    delete _canvas;
}

void Screen::init()
{
    Screenable::init();

    _canvas->setScene(_scene);

    std::function<void()> drawCall = [&](){
        if(_scene->isReady())
            _scene->draw();
    };

    _canvas->setDrawCall(drawCall);

    _canvas->setAssetsStorage(_assetsStorage);
}

void Screen::drawContents()
{
    //_canvas->draw();
}

bool Screen::keyboardEvent(int key, int scancode, int action, int modifiers)
{
    if (nanogui::Screen::keyboardEvent(key, scancode, action, modifiers))
        return true;
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
          case GLFW_KEY_ESCAPE:
            setVisible(false);
            return true;
            break;
          default:
            break;
        }
    }
    _canvas->keyboardEvent(key, scancode, action, modifiers);
    return false;
}

void Screen::draw(NVGcontext *ctx)
{
    nanogui::Screen::draw(ctx);
}
