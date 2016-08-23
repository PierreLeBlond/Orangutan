#include "core/qtrenderer.h"

using namespace std;

QTRenderer::QTRenderer(QWidget* parent, GLuint width, GLuint height) : QOpenGLWidget(parent), _width(width), _height(height), _drawCall([](){})
{
}

void QTRenderer::initializeGL()
{
    QOpenGLFunctions_4_3_Core* funcs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    if (!funcs) {
        cerr << "Could not obtain required OpenGL context version" << endl;
        exit(1);
    }
    funcs->initializeOpenGLFunctions();
    OpenGLFunction::Instance().setFunctionsPointer(funcs);

    const GLubyte *renderer = OpenGLFunction::functions().glGetString(GL_RENDERER);
    const GLubyte *vendor = OpenGLFunction::functions().glGetString(GL_VENDOR);
    const GLubyte *version = OpenGLFunction::functions().glGetString(GL_VERSION);
    const GLubyte *glslVersion = OpenGLFunction::functions().glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    OpenGLFunction::functions().glGetIntegerv(GL_MAJOR_VERSION, &major);
    OpenGLFunction::functions().glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::cout << "GL Vendor                      : " << vendor << std::endl;
    std::cout << "GL Renderer                    : " << renderer << std::endl;
    std::cout << "GL Version (string)            : " << version << std::endl;
    std::cout << "GL Version (integer)           : " << major << "." << minor << std::endl;
    std::cout << "GLSL Version                   : " << glslVersion  << std::endl;

    OpenGLFunction::functions().glClearColor(0.3f, 0.37f, 0.56f, 1.0f);

    OpenGLFunction::functions().glEnable(GL_DEPTH_TEST);

    OpenGLFunction::functions().glDisable(GL_BLEND);

    OpenGLFunction::functions().glDisable(GL_CULL_FACE);

    OpenGLFunction::functions().glEnable(GL_TEXTURE_2D);
}

void QTRenderer::init()
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
}

void QTRenderer::start()
{
    int sec = 1000;
    int timerInterval = sec / 60;
    _timer.start(timerInterval);
}

void QTRenderer::paintGL()
{
    makeCurrent();

    _drawCall();

    OpenGLFunction::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void QTRenderer::resizeGL(int width, int height)
{
    _width = width;
    _height = height;
    OpenGLFunction::functions().glViewport(0, 0, _width, _height);
}

void QTRenderer::createFrameBuffer(GLuint *fboHandle, GLuint *depthBuf, GLuint *renderTex1, GLuint *renderTex2)
{
    OpenGLFunction::functions().glGenFramebuffers(1, fboHandle);
    OpenGLFunction::functions().glBindFramebuffer(GL_FRAMEBUFFER, *fboHandle);

    OpenGLFunction::functions().glGenTextures(1, renderTex1);
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, *renderTex1);
    OpenGLFunction::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    OpenGLFunction::functions().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *renderTex1, 0);

    OpenGLFunction::functions().glGenTextures(1, renderTex2);
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, *renderTex2);
    OpenGLFunction::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    OpenGLFunction::functions().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, *renderTex2, 0);

    OpenGLFunction::functions().glGenRenderbuffers(1, depthBuf);
    OpenGLFunction::functions().glBindRenderbuffer(GL_RENDERBUFFER, *depthBuf);
    OpenGLFunction::functions().glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);

    OpenGLFunction::functions().glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depthBuf);
}

void QTRenderer::setDrawCall(std::function<void()> drawCall)
{
    _drawCall = drawCall;
}

void QTRenderer::timeOutSlot()
{
    update();
}
