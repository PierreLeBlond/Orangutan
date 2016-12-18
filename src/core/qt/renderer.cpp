#include "core/qt/renderer.h"
#include "core/debug.h"

using namespace std;

Renderer::Renderer(QWidget* parent, GLuint width, GLuint height) :
    Rendererable(width, height),
    QOpenGLWidget(parent)
{
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
}

void Renderer::start()
{
    int sec = 1000;
    int timerInterval = sec / 60;
    _timer.start(timerInterval);
}

void Renderer::stop()
{
    _timer.stop();
}

void Renderer::paintGL()
{
    makeCurrent();
    //Context::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _drawCall();
}

void Renderer::resize(int width, int height)
{
    Rendererable::resize(width, height);
    Context::functions().glViewport(0, 0, _width, _height);
}

void Renderer::createFrameBuffer(GLuint *fboHandle, GLuint *depthBuf, GLuint *renderTex1, GLuint *renderTex2)
{
    Context::functions().glGenFramebuffers(1, fboHandle);
    Context::functions().glBindFramebuffer(GL_FRAMEBUFFER, *fboHandle);

    Context::functions().glGenTextures(1, renderTex1);
    //Context::functions().glActiveTexture(GL_TEXTURE0);
    Context::functions().glBindTexture(GL_TEXTURE_2D, *renderTex1);
    Context::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    Context::functions().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *renderTex1, 0);

    Context::functions().glGenTextures(1, renderTex2);
    //Context::functions().glActiveTexture(GL_TEXTURE0);
    Context::functions().glBindTexture(GL_TEXTURE_2D, *renderTex2);
    Context::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    Context::functions().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, *renderTex2, 0);

    Context::functions().glGenRenderbuffers(1, depthBuf);
    Context::functions().glBindRenderbuffer(GL_RENDERBUFFER, *depthBuf);
    Context::functions().glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);

    Context::functions().glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depthBuf);
}

void Renderer::timeOutSlot()
{
    update();
}
