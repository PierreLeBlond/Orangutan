#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <functional>

#include "core/qt/context.h"
#include "core/rendererable.h"

#include <QOpenGLWidget>
#include <QObject>
#include <QTimer>

class Renderer : public QOpenGLWidget,
public Rendererable
{
    Q_OBJECT
public:
                                                Renderer(QWidget *parent = 0);
    virtual                                     ~Renderer();

    virtual void                                init();
    virtual void                                start();
    virtual void                                stop();

    //Mandatory
    virtual void                                initializeGL();
    virtual void                                resizeGL(int width, int height);
    virtual void                                paintGL();

    virtual void                                createFrameBuffer(unsigned int *fboHandle, unsigned int *depthBuf, unsigned int *renderTex1, unsigned int *renderTex2, int width, int height);

private slots:
    void                                        timeOutSlot();

private:
    QTimer                                      _timer;
};

#endif // RENDERER_H
