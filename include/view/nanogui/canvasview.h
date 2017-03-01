#ifndef CANVAS_VIEW_H
#define CANVAS_VIEW_H

#include <nanogui/glcanvas.h>
#include <nanogui/opengl.h>

class CanvasView : public nanogui::GLCanvas
{
public:
                                                CanvasView(nanogui::Widget *parent = nullptr,
                                                       unsigned int width = 600,
                                                       unsigned int height = 400);

    void                                        start();
    void                                        stop();

    void                                        setDrawCall(const std::function<void()>& drawcall);

    virtual void                                drawGL();

    virtual bool                                mouseMotionEvent(const Eigen::Vector2i &p,
                                                                 const Eigen::Vector2i &rel,
                                                                 int button, int modifiers);

    virtual bool                                mouseButtonEvent(const Eigen::Vector2i &p,
                                                                 int button,
                                                                 bool down,
                                                                 int modifiers);

private:
    bool                                        _draw;
    Eigen::Vector2i                             _lastMousePosition;
    bool                                        _mouseIsPressed;

    std::function<void()>                       _drawCall;
};

#endif // CANVAS_VIEW_H
