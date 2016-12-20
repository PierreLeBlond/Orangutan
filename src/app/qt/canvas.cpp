#include "app/qt/canvas.h"

Canvas::Canvas(QWidget* parent, unsigned int width, unsigned int height) :
Canvasable(width, height),
Renderer(parent)
{
    //resize(width, height);
}

Canvas::~Canvas()
{
}

/*void RenderingWindow::paintGL(){
    makeCurrent();

    OpenGLFunction::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(_asAScene && _scene != 0 && _scene->isReady())
    {
        GLuint fboHandle = -1, renderTex[2], depthBuf;
        int swap = 0;
        for(int i = 0; i < _screenSpaceShader.size();i++){
        if(_screenSpaceShader[i]){//Rendu en différé : premier rendu dans une texture, puis modification de la texture

            if(fboHandle == -1){
                createFrameBuffer(&fboHandle, &depthBuf, &renderTex[0], &renderTex[1]);

                if(swap%2 == 0){
                    OpenGLFunction::functions().glDrawBuffer(GL_COLOR_ATTACHMENT0);
                }else{
                    OpenGLFunction::functions().glDrawBuffer(GL_COLOR_ATTACHMENT1);
                }

                OpenGLFunction::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                _scene->draw();

            }else{

                //OpenGLFunction::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



                if(swap%2 == 0){
                    _scene->getScreenSpaceRenderable()->setRenderMapId(renderTex[1]);
                    OpenGLFunction::functions().glDrawBuffer(GL_COLOR_ATTACHMENT0);
                }else{
                    _scene->getScreenSpaceRenderable()->setRenderMapId(renderTex[0]);
                    OpenGLFunction::functions().glDrawBuffer(GL_COLOR_ATTACHMENT1);
                }

                OpenGLFunction::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                _scene->drawScreenSpace();

            }

            _scene->getScreenSpaceRenderable()->setShaderStrategy(_assetsStorage->getScreenSpaceShaderStrategy(i));
            _scene->getScreenSpaceRenderable()->fillInVBO();
            _scene->getScreenSpaceRenderable()->createVertexArrayObject();

             swap++;

        }
        }

        OpenGLFunction::functions().glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());
        OpenGLFunction::functions().glDrawBuffer(GL_COLOR_ATTACHMENT0);
        OpenGLFunction::functions().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(fboHandle == -1){
            _scene->draw();
        }else{
            if(swap%2 == 0){
                _scene->getScreenSpaceRenderable()->setRenderMapId(renderTex[1]);
            }else{
                _scene->getScreenSpaceRenderable()->setRenderMapId(renderTex[0]);
            }
            _scene->drawScreenSpace();

        }

        OpenGLFunction::functions().glDeleteRenderbuffers(1, &depthBuf);
        OpenGLFunction::functions().glDeleteTextures(1, &renderTex[0]);
        OpenGLFunction::functions().glDeleteTextures(1, &renderTex[1]);
        OpenGLFunction::functions().glDeleteFramebuffers(1, &fboHandle);

        OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);
    }
}*/

void Canvas::resizeGL(int width, int height)
{
    Canvasable::resize(width, height);
    Renderer::resizeGL(width, height);
}

void Canvas::resize(int width, int height)
{
    Canvasable::resize(width, height);
    Renderer::resizeGL(width, height);
}

void Canvas::keyPressEvent(QKeyEvent *keyEvent)
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
    case Qt::Key_W:
        _scene->getCurrentCamera()->move(FORWARD);
        break;
    case Qt::Key_S:
       _scene->getCurrentCamera()->move(BACKWARD);
        break;
    case Qt::Key_A:
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
        _scene->getCurrentObject()->move(FORWARD);
        break;
    case Qt::Key_2:
        _scene->getCurrentObject()->move(BACKWARD);
        break;
    case Qt::Key_4:
        _scene->getCurrentObject()->move(LEFT);
        break;
    case Qt::Key_6:
        _scene->getCurrentObject()->move(RIGHT);
        break;
    case Qt::Key_9:
        _scene->getCurrentObject()->move(UP);
        break;
    case Qt::Key_3:
        _scene->getCurrentObject()->move(DOWN);
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

void Canvas::mousePressEvent(QMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    _mouseIsPressed = true;
    _lastMousePosition = mouseEvent->pos();
}

void Canvas::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(_mouseIsPressed){
        QPoint newMousePosition = mouseEvent->pos();
        QPoint displacementVector = newMousePosition - _lastMousePosition;
        _scene->getCurrentCamera()->pitch(-(GLfloat)displacementVector.y());
        _scene->getCurrentCamera()->yaw((GLfloat)displacementVector.x());
        _lastMousePosition = mouseEvent->pos();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    _mouseIsPressed = false;
}

void Canvas::wheelEvent(QWheelEvent *wheelEvent)
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
