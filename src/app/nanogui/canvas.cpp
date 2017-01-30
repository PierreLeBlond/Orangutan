#include "app/nanogui/canvas.h"
#include "util/keyboard.h"

Canvas::Canvas(GLFWwindow *GLFWWindow, nanogui::Widget* parent, unsigned int width, unsigned int height) :
    _GLFWWindow(GLFWWindow),
    Canvasable(width, height),
    nanogui::GLCanvas(parent)
{
    resize(width, height);

    nanogui::Color color(0.3f, 0.0f, 0.56f, 1.0f);

    setBackgroundColor(color);

}

Canvas::~Canvas()
{
}

void Canvas::resize(int width, int height)
{
    Canvasable::resize(width, height);
    setWidth(width);
    setHeight(height);
}

void Canvas::drawGL()
{
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_BLEND);

    glDisable(GL_CULL_FACE);

    _drawCall();
}

bool Canvas::keyboardEvent(int key, int scancode, int action, int modifiers)
{
    if(action == GLFW_PRESS /*&& Keyboard::instance().getState(key) != KEYDOWN*/)
    {
        Keyboard::instance().setState(key, KEYDOWN);
    }
    else if(action == GLFW_RELEASE)
    {
        Keyboard::instance().setState(key, KEYUP);
    }
    return true;
}

bool Canvas::mouseMotionEvent(const Eigen::Vector2i &p, const Eigen::Vector2i &rel, int button, int modifiers)
{
    if(_mouseIsPressed)
    {
        Eigen::Vector2i newMousePosition = p;
        Eigen::Vector2i displacementVector = newMousePosition - _lastMousePosition;
        _scene->getCurrentCamera()->pitch(-(float)displacementVector.y());
        _scene->getCurrentCamera()->yaw((float)displacementVector.x());
        _scene->getCurrentCamera()->update();
        _lastMousePosition = p;
    }

    return false;
}

bool Canvas::mouseButtonEvent(const Eigen::Vector2i &p, int button, bool down, int modifiers)
{
    std::cout << "mouse : " << down << std::endl;
    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if(down)
        {
            _lastMousePosition = p;
            _mouseIsPressed = true;
        }
        else
        {
            _mouseIsPressed = false;
        }
    }
    return false;
}

bool Canvas::scrollEvent(const Eigen::Vector2i &p, const Eigen::Vector2f &rel)
{
    /*if(wheelEvent->orientation() == Qt::Vertical)
    {
        if(wheelEvent->delta() > 0)
            _scene->getCurrentCamera()->move(UP);
        else if(wheelEvent->delta() < 0)
            _scene->getCurrentCamera()->move(DOWN);
    }
    else if(wheelEvent->orientation() == Qt::Horizontal)
    {
        if(wheelEvent->delta() > 0)
            _scene->getCurrentCamera()->roll(-10.0f);
        else if(wheelEvent->delta() < 0)
            _scene->getCurrentCamera()->roll(10.0f);
    }*/
    return false;
}

void Canvas::createFrameBuffer(unsigned int *fboHandle, unsigned int *depthBuf, unsigned int *renderTex1, unsigned int *renderTex2, int width, int height)
{
}
