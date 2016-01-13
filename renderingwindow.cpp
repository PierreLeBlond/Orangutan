#include "renderingwindow.h"

RenderingWindow::RenderingWindow(QWidget* parent, GLuint width, GLuint height) : QOpenGLWidget(parent), _asAScene(false), _mouseIsPressed(false)
{
    _width = width;
    _height = height;
}

RenderingWindow::~RenderingWindow()
{
    _scene = NULL;
}

void RenderingWindow::initializeGL(){

    QOpenGLFunctions_3_3_Core* funcs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    if (!funcs) {
        qWarning() << "Could not obtain required OpenGL context version";
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

void RenderingWindow::init(){
    connect(&_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
}

void RenderingWindow::start(){
    int sec = 1000;
    int timerInterval = sec / 60;
    _timer.start(timerInterval);
}

void RenderingWindow::paintGL(){
    makeCurrent();
    OpenGLFunction::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(_asAScene && _scene != 0 && _scene->isReady())
    {
        _scene->draw();
    }
}

void RenderingWindow::resizeGL(int width, int height)
{
    if(_scene)
    {
        _scene->getCurrentCamera()->setWidth(width);
        _width = width;
        _scene->getCurrentCamera()->setHeight(height);
        _height = height;
    }
    OpenGLFunction::functions().glViewport(0, 0, _width, _height);
}

void RenderingWindow::timeOutSlot()
{
    update();
}

void RenderingWindow::setScene(std::shared_ptr<Scene> scene){
    _scene = scene;
    _asAScene = true;
}

void RenderingWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_Up:
        _scene->getCurrentCamera()->pitch(10.0f);
        break;
    case Qt::Key_Down:
        _scene->getCurrentCamera()->pitch(-10.0f);
        break;
    case Qt::Key_Right:
        _scene->getCurrentCamera()->yaw(10.0f);
        break;
    case Qt::Key_Left:
        _scene->getCurrentCamera()->yaw(-10.0f);
        break;
    case Qt::Key_Z:
        _scene->getCurrentCamera()->move(FORWARD);
        break;
    case Qt::Key_S:
       _scene->getCurrentCamera()->move(BACKWARD);
        break;
    case Qt::Key_Q:
        _scene->getCurrentCamera()->move(LEFT);
        break;
    case Qt::Key_D:
        _scene->getCurrentCamera()->move(RIGHT);
        break;
    case Qt::Key_O:
        _scene->getCurrentCamera()->setOrthoProjectionMode();
        break;
    case Qt::Key_P:
        _scene->getCurrentCamera()->setPerspectiveProjectionMode();
        break;
    case Qt::Key_8:
        _scene->getCurrentTransformable()->move(FORWARD);
        break;
    case Qt::Key_2:
        _scene->getCurrentTransformable()->move(BACKWARD);
        break;
    case Qt::Key_4:
        _scene->getCurrentTransformable()->move(LEFT);
        break;
    case Qt::Key_6:
        _scene->getCurrentTransformable()->move(RIGHT);
        break;
    case Qt::Key_9:
        _scene->getCurrentTransformable()->move(UP);
        break;
    case Qt::Key_3:
        _scene->getCurrentTransformable()->move(DOWN);
        break;
    case Qt::Key_Plus:
        _scene->getCurrentCamera()->move(UP);
        break;
    case Qt::Key_Minus:
        _scene->getCurrentCamera()->move(DOWN);
        break;
    case Qt::Key_Space:
        //screenShot();
        break;
    case Qt::Key_Control:
        _scene->getCurrentCamera()->roll(-10.0f);
        break;
    case Qt::Key_Shift:
        _scene->getCurrentCamera()->roll(10.0f);
        break;
    default:
        break;
    }
}

void RenderingWindow::mousePressEvent(QMouseEvent *mouseEvent)
{
    /*_originRubberBand = mouseEvent->pos();
    if(!_rubberBand)
        _rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    _rubberBand->setGeometry(QRect(_originRubberBand, QSize()));
    _rubberBand->show();*/
    _mouseIsPressed = true;
    _lastMousePosition = mouseEvent->pos();
}

void RenderingWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    //_rubberBand->setGeometry(QRect(_originRubberBand, mouseEvent->pos()).normalized());
    if(_mouseIsPressed){
        QPoint newMousePosition = mouseEvent->pos();
        QPoint displacementVector = newMousePosition - _lastMousePosition;
        //std::cout << "X : " << displacementVector.x() << " , Y : " << displacementVector.y();
        _scene->getCurrentCamera()->pitch(-(GLfloat)displacementVector.y());
        _scene->getCurrentCamera()->yaw((GLfloat)displacementVector.x());
        _lastMousePosition = mouseEvent->pos();
    }
}

void RenderingWindow::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    /*if(_rubberBand->width() > 100 && _rubberBand->height() > 100)
    {
        //resizeGL(_rubberBand->width(), _rubberBand->height());
    }
    _rubberBand->hide();*/
    _mouseIsPressed = false;
}

void RenderingWindow::wheelEvent(QWheelEvent *wheelEvent)
{
    if(wheelEvent->orientation() == Qt::Vertical)
    {
        if(wheelEvent->delta() > 0)
            _scene->getCurrentCamera()->move(UP);
        else if(wheelEvent->delta() < 0)
            _scene->getCurrentCamera()->move(DOWN);
    }
    else if(wheelEvent->orientation() == Qt::Horizontal)
    {
        if(wheelEvent->delta() > 0)
            _scene->getCurrentCamera()->roll(-10.0f);
        else if(wheelEvent->delta() < 0)
            _scene->getCurrentCamera()->roll(10.0f);
    }

}
