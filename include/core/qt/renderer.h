#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <functional>

#include "core/qt/context.h"
#include "core/rendererable.h"

#include <QOpenGLWidget>
#include <QObject>
#include <QTimer>

class Renderer : public Rendererable, public QOpenGLWidget
{
    Q_OBJECT
public:
                                                Renderer(QWidget *parent = 0, GLuint width = 600, GLuint height = 400);
    virtual                                     ~Renderer();

    virtual void                                init();
    virtual void                                start();
    virtual void                                stop();

    virtual void                                resize(int width, int height);

    //Mandatory
    void                                        paintGL();


    virtual void                                createFrameBuffer(GLuint *fboHandle, GLuint *depthBuf, GLuint *renderTex1, GLuint *renderTex2);

private slots:
    void                                        timeOutSlot();

private:
    QTimer                                      _timer;
};

#endif // RENDERER_H
