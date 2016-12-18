#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QDebug>
#include <QObject>

#include "scene/scene.h"
#include "app/canvasable.h"
#include "core/qt/renderer.h"

class Canvas : public Canvasable, public Renderer
{
    Q_OBJECT
public:
                                                Canvas(QWidget *parent = 0, GLuint width = 600, GLuint height = 400);
    virtual                                     ~Canvas();

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
