#ifndef RENDERERABLE_H
#define RENDERERABLE_H
#include <GL/gl.h>

#include <iostream>
#include <functional>

class Rendererable
{
public:
                                                Rendererable(GLuint width = 600, GLuint height = 400);
    virtual                                     ~Rendererable() = 0;

    virtual void                                init() = 0;
    virtual void                                start() = 0;
    virtual void                                stop() = 0;

    virtual void                                resize(int width, int height);

    void                                        setDrawCall(std::function<void()> drawCall);

    virtual void                                createFrameBuffer(GLuint *fboHandle, GLuint *depthBuf, GLuint *renderTex1, GLuint *renderTex2) = 0;

protected:
    int                                         _width;
    int                                         _height;

    std::function<void()>                       _drawCall;
};


#endif // RENDERERABLE_H
