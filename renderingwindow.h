#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QDebug>
#include <QObject>

#include "Scene.h"


class RenderingWindow  : public QOpenGLWidget
{
    Q_OBJECT
public:
                                                RenderingWindow(QWidget *parent = 0, GLuint width = 600, GLuint height = 400);
                                                ~RenderingWindow();

    void                                        initializeGL();
    void                                        init();
    void                                        start();
    void                                        resizeGL(int width, int height);
    void                                        paintGL();

    void                                        setScene(std::shared_ptr<Scene> scene);

    void                                        keyPressEvent(QKeyEvent *keyEvent);

    void                                        mouseMoveEvent(QMouseEvent *mouseEvent);

    void                                        mousePressEvent(QMouseEvent *mouseEvent);

    void                                        mouseReleaseEvent(QMouseEvent *mouseEvent);

    void                                        wheelEvent(QWheelEvent *wheelEvent);


private slots:

    void                                        timeOutSlot();

private:
    std::shared_ptr<Scene>                      _scene;
    GLuint                                      _width;
    GLuint                                      _height;

    QTimer                                      _timer;

    bool                                        _asAScene;

    QPoint                                      _lastMousePosition;
    bool                                        _mouseIsPressed;
};

#endif // RENDERINGWINDOW_H
