#ifndef QT_RENDERER_H
#define QT_RENDERER_H

#include <QOpenGLWidget>
#include <QObject>
#include <QTimer>

#include <iostream>
#include <functional>

#include "core/opengl.h"

class QTRenderer : public QOpenGLWidget
{
    Q_OBJECT
public:
                                                QTRenderer(QWidget *parent = 0, GLuint width = 600, GLuint height = 400);

    void                                        initializeGL();
    void                                        init();
    void                                        start();
    void                                        resizeGL(int width, int height);
    void                                        paintGL();

    void                                        setDrawCall(std::function<void()> drawCall);

    void                                        createFrameBuffer(GLuint *fboHandle, GLuint *depthBuf, GLuint *renderTex1, GLuint *renderTex2);

private slots:

    void                                        timeOutSlot();

private:
    int                                         _width;
    int                                         _height;

    QTimer                                      _timer;

    std::function<void()>                       _drawCall;
};


#endif // QT_RENDERER_H
