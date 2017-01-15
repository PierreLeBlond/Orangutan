#include "app/nanogui/screen.h"
#include "app/nanogui/maintool.h"
#include "app/nanogui/objecttool.h"
#include "core/debug.h"

#include <nanogui/window.h>
#include <nanogui/layout.h>

Screen::Screen(int width, int height, std::string name, bool b) :
    nanogui::Screen(Eigen::Vector2i(width, height), name, b),
    _mainTool(this, "Main")
{
    //this->setFixedSize(Eigen::Vector2i(900, 600));
    //this->setPosition(Eigen::Vector2i(0, 0));

    nanogui::Window *window = new nanogui::Window(this, "Canvas");
    window->setPosition(Eigen::Vector2i(300, 0));
    window->setFixedSize(Eigen::Vector2i(600, 600));
    window->setLayout(new nanogui::GroupLayout());

    _canvas = new Canvas(glfwWindow(), window);
    _canvas->resize(600, 600);
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
        {
            _scene->animate();
            _scene->draw();
        }
    };

    _canvas->setDrawCall(drawCall);

    _canvas->setAssetsStorage(_assetsStorage);

    _mainTool.setAssetsStorage(_assetsStorage);
    _mainTool.setCurrentObject(_scene->getCurrentRenderableObject());

    _mainTool.init();

    performLayout();
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
