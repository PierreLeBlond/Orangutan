#include "core/qt/renderer.h"
#include "core/qt/context.h"
#include "core/debug.h"

using namespace std;

Renderer::Renderer(QWidget* parent) :
    QOpenGLWidget(parent)
{
}

Renderer::~Renderer()
{
}

void Renderer::initializeGL()
{
    QOpenGLFunctions_4_5_Core* funcs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_5_Core>();
    if (!funcs) {
        cerr << "Could not obtain required OpenGL context version" << endl;
        exit(1);
    }
    funcs->initializeOpenGLFunctions();
    Context::instance().setFunctionsPointer(funcs);

    const GLubyte *renderer = Context::functions().glGetString(GL_RENDERER);
    const GLubyte *vendor = Context::functions().glGetString(GL_VENDOR);
    const GLubyte *version = Context::functions().glGetString(GL_VERSION);
    const GLubyte *glslVersion = Context::functions().glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    Context::functions().glGetIntegerv(GL_MAJOR_VERSION, &major);
    Context::functions().glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::cout << "GL Vendor                      : " << vendor << std::endl;
    std::cout << "GL Renderer                    : " << renderer << std::endl;
    std::cout << "GL Version (string)            : " << version << std::endl;
    std::cout << "GL Version (integer)           : " << major << "." << minor << std::endl;
    std::cout << "GLSL Version                   : " << glslVersion  << std::endl;

    Context::functions().glClearColor(0.3f, 0.0f, 0.56f, 1.0f);

    Context::functions().glEnable(GL_DEPTH_TEST);

    Context::functions().glDisable(GL_BLEND);

    Context::functions().glDisable(GL_CULL_FACE);
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

void Renderer::resizeGL(int width, int height)
{
    Context::functions().glViewport(0, 0, width, height);
}

void Renderer::createFrameBuffer(GLuint *fboHandle, GLuint *depthBuf,
                                 GLuint *renderTex1, GLuint *renderTex2,
                                 int width, int height)
{
    Context::functions().glGenFramebuffers(1, fboHandle);
    Context::functions().glBindFramebuffer(GL_FRAMEBUFFER, *fboHandle);

    Context::functions().glGenTextures(1, renderTex1);
    //Context::functions().glActiveTexture(GL_TEXTURE0);
    Context::functions().glBindTexture(GL_TEXTURE_2D, *renderTex1);
    Context::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    Context::functions().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *renderTex1, 0);

    Context::functions().glGenTextures(1, renderTex2);
    //Context::functions().glActiveTexture(GL_TEXTURE0);
    Context::functions().glBindTexture(GL_TEXTURE_2D, *renderTex2);
    Context::functions().glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Context::functions().glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    Context::functions().glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, *renderTex2, 0);

    Context::functions().glGenRenderbuffers(1, depthBuf);
    Context::functions().glBindRenderbuffer(GL_RENDERBUFFER, *depthBuf);
    Context::functions().glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    Context::functions().glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depthBuf);
}

void Renderer::timeOutSlot()
{
    update();
}

#include "moc_renderer.cpp"
