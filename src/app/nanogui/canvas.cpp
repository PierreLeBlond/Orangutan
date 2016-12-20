#include "app/nanogui/canvas.h"

Canvas::Canvas(nanogui::Widget* parent, unsigned int width, unsigned int height) :
Canvasable(width, height),
nanogui::GLCanvas(parent)
{
    resize(width, height);
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
    _drawCall();
}

bool Canvas::keyboardEvent(int key, int scancode, int action, int modifiers)
{
    if(action == GLFW_PRESS)
    {
        switch(key)
        {
          case GLFW_KEY_ESCAPE:
            //close();
            break;
          case GLFW_KEY_UP:
            _scene->getCurrentCamera()->pitch(10.0f);
            break;
          case GLFW_KEY_DOWN:
            _scene->getCurrentCamera()->pitch(-10.0f);
            break;
          case GLFW_KEY_RIGHT:
            _scene->getCurrentCamera()->yaw(10.0f);
            break;
          case GLFW_KEY_LEFT:
            _scene->getCurrentCamera()->yaw(-10.0f);
            break;
          case GLFW_KEY_W:
            _scene->getCurrentCamera()->move(FORWARD);
            break;
          case GLFW_KEY_S:
            _scene->getCurrentCamera()->move(BACKWARD);
            break;
          case GLFW_KEY_A:
            _scene->getCurrentCamera()->move(LEFT);
            break;
          case GLFW_KEY_D:
            _scene->getCurrentCamera()->move(RIGHT);
            break;
          case GLFW_KEY_O:
            _scene->getCurrentCamera()->setOrthoProjectionMode();
            break;
          case GLFW_KEY_P:
            _scene->getCurrentCamera()->setPerspectiveProjectionMode();
            break;
          case GLFW_KEY_8:
            _scene->getCurrentObject()->move(FORWARD);
            break;
          case GLFW_KEY_2:
            _scene->getCurrentObject()->move(BACKWARD);
            break;
          case GLFW_KEY_4:
            _scene->getCurrentObject()->move(LEFT);
            break;
          case GLFW_KEY_6:
            _scene->getCurrentObject()->move(RIGHT);
            break;
          case GLFW_KEY_9:
            _scene->getCurrentObject()->move(UP);
            break;
          case GLFW_KEY_3:
            _scene->getCurrentObject()->move(DOWN);
            break;
          case GLFW_KEY_KP_ADD:
            _scene->getCurrentCamera()->move(UP);
            break;
          case GLFW_KEY_KP_SUBTRACT:
            _scene->getCurrentCamera()->move(DOWN);
            break;
          case GLFW_KEY_SPACE:
            //screenShot();
            break;
          case GLFW_KEY_LEFT_CONTROL:
            _scene->getCurrentCamera()->roll(-10.0f);
            break;
          case GLFW_KEY_LEFT_SHIFT:
            _scene->getCurrentCamera()->roll(10.0f);
            break;
          default:
            return false;
            break;
        }
    }
    return true;
}

bool Canvas::mouseMotionEvent(const Eigen::Vector2i &p, const Eigen::Vector2i &rel, int button, int modifiers)
{
    _mouseIsPressed = true;
    //_lastMousePosition = mouseEvent->pos();
    return false;
}

bool Canvas::mouseButtonEvent(const Eigen::Vector2i &p, int button, bool down, int modifiers)
{
    /*if(_mouseIsPressed){
        QPoint newMousePosition = mouseEvent->pos();
        QPoint displacementVector = newMousePosition - _lastMousePosition;
        _scene->getCurrentCamera()->pitch(-(GLfloat)displacementVector.y());
        _scene->getCurrentCamera()->yaw((GLfloat)displacementVector.x());
        _lastMousePosition = mouseEvent->pos();
    }*/
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
