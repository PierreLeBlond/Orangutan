#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QDebug>
#include <QObject>

#include "scene.h"


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
    void                                        setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

    void                                        enableScreenSpaceShader(int index);

    void                                        createFrameBuffer(GLuint *fboHandle, GLuint *depthBuf, GLuint *renderTex1, GLuint *renderTex2);

    void                                        keyPressEvent(QKeyEvent *keyEvent);

    void                                        mouseMoveEvent(QMouseEvent *mouseEvent);

    void                                        mousePressEvent(QMouseEvent *mouseEvent);

    void                                        mouseReleaseEvent(QMouseEvent *mouseEvent);

    void                                        wheelEvent(QWheelEvent *wheelEvent);


private slots:

    void                                        timeOutSlot();

private:
    std::shared_ptr<AssetsStorage>              _assetsStorage;

    std::shared_ptr<Scene>                      _scene;
    GLuint                                      _width;
    GLuint                                      _height;

    QTimer                                      _timer;

    bool                                        _asAScene;

    std::vector<bool>                           _screenSpaceShader;

    QPoint                                      _lastMousePosition;
    bool                                        _mouseIsPressed;
};

#endif // RENDERINGWINDOW_H
