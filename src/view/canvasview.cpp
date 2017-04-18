#include "view/canvasview.h"

CanvasView::CanvasView(nanogui::Widget* parent, unsigned int width, unsigned int height) :
    nanogui::GLCanvas(parent),
    _draw(false),
    _mouseIsPressed(false),
    _drawCall([](){})
{
    setSize(Eigen::Vector2i(width, height));

    nanogui::Color color(0.3f, 0.0f, 0.56f, 1.0f);

    setBackgroundColor(color);
    setDrawBorder(true);
}

void CanvasView::start()
{
    _draw = true;
}

void CanvasView::stop()
{
    _draw = false;
}

void CanvasView::setDrawCall(const std::function<void()>& drawcall)
{
    _drawCall = drawcall;
}

void CanvasView::drawGL()
{
    if(_draw)
    {
        glEnable(GL_DEPTH_TEST);

        glDisable(GL_BLEND);

        glDisable(GL_CULL_FACE);

        _drawCall();
    }
}

bool CanvasView::mouseMotionEvent(const Eigen::Vector2i &p, const Eigen::Vector2i &rel, int button, int modifiers)
{
    if(_mouseIsPressed)
    {
        Eigen::Vector2i newMousePosition = p;
        Eigen::Vector2i displacementVector = newMousePosition - _lastMousePosition;
        //_scene->getCurrentCamera()->pitch(-(float)displacementVector.y());
        //_scene->getCurrentCamera()->yaw((float)displacementVector.x());
        //_scene->getCurrentCamera()->update();
        _lastMousePosition = p;
    }

    return true;
}

bool CanvasView::mouseButtonEvent(const Eigen::Vector2i &p, int button, bool down, int modifiers)
{
    //std::cout << "mouse : " << down << std::endl;
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
    return true;
}

