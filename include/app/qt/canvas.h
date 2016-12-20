#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

#include "scene/scene.h"
#include "app/canvasable.h"
#include "core/qt/renderer.h"

class Canvas : public Canvasable, public Renderer
{
public:
                                                Canvas(QWidget *parent = 0, unsigned int width = 600, unsigned int height = 400);
    virtual                                     ~Canvas();

    virtual void                                resizeGL(int width, int height);
    virtual void                                resize(int width, int height);

    void                                        keyPressEvent(QKeyEvent *keyEvent);

    void                                        mouseMoveEvent(QMouseEvent *mouseEvent);

    void                                        mousePressEvent(QMouseEvent *mouseEvent);

    void                                        mouseReleaseEvent(QMouseEvent *mouseEvent);

    void                                        wheelEvent(QWheelEvent *wheelEvent);

private:
    QPoint                                      _lastMousePosition;
};

#endif // CANVAS_H
