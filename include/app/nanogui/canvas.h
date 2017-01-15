#ifndef CANVAS_H
#define CANVAS_H

#include "scene/scene.h"
#include "app/canvasable.h"
#include "core/rendererable.h"

#include <nanogui/glcanvas.h>
#include <nanogui/opengl.h>

class Canvas : public Canvasable, public nanogui::GLCanvas, public Rendererable
{
public:
                                                Canvas(GLFWwindow *GLFWWindow, nanogui::Widget *parent = 0, unsigned int width = 600, unsigned int height = 400);
    virtual                                     ~Canvas();

    virtual void                                init(){};
    virtual void                                start(){};
    virtual void                                stop(){};

    virtual void                                resize(int width, int height);

    virtual void                                drawGL();

    virtual bool                                keyboardEvent(int key, int scancode, int action, int modifiers);

    virtual bool                                mouseMotionEvent(const Eigen::Vector2i &p, const Eigen::Vector2i &rel, int button, int modifiers);

    virtual bool                                mouseButtonEvent(const Eigen::Vector2i &p, int button, bool down, int modifiers);

    virtual bool                                scrollEvent(const Eigen::Vector2i &p, const Eigen::Vector2f &rel);

    virtual void                                createFrameBuffer(unsigned int *fboHandle, unsigned int *depthBuf, unsigned int *renderTex1, unsigned int *renderTex2, int width, int height);

private:
    Eigen::Vector2i                             _lastMousePosition;
    GLFWwindow*                                 _GLFWWindow;
};

#endif // CANVAS_H
