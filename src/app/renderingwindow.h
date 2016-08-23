#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QDebug>
#include <QObject>

#include "scene/scene.h"
#include "core/qtrenderer.h"


class RenderingWindow : public QTRenderer
{
    Q_OBJECT
public:
                                                RenderingWindow(QWidget *parent = 0, GLuint width = 600, GLuint height = 400);
                                                ~RenderingWindow();

    void                                        setScene(std::shared_ptr<Scene> scene);
    void                                        setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

    void                                        enableScreenSpaceShader(int index);

    void                                        resizeGL(int width, int height);

    void                                        keyPressEvent(QKeyEvent *keyEvent);

    void                                        mouseMoveEvent(QMouseEvent *mouseEvent);

    void                                        mousePressEvent(QMouseEvent *mouseEvent);

    void                                        mouseReleaseEvent(QMouseEvent *mouseEvent);

    void                                        wheelEvent(QWheelEvent *wheelEvent);

private:
    std::shared_ptr<AssetsStorage>              _assetsStorage;

    std::shared_ptr<Scene>                      _scene;
    GLuint                                      _width;
    GLuint                                      _height;

    bool                                        _asAScene;

    std::vector<bool>                           _screenSpaceShader;

    QPoint                                      _lastMousePosition;
    bool                                        _mouseIsPressed;
};

#endif // RENDERINGWINDOW_H
