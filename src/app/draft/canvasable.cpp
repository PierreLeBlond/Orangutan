#include "app/canvasable.h"

Canvasable::Canvasable(unsigned int width, unsigned int height) : _width(width), _height(height),
 _asAScene(false), _mouseIsPressed(false)
{
    _screenSpaceShader.push_back(false);
    _screenSpaceShader.push_back(false);
    _screenSpaceShader.push_back(false);
}

Canvasable::~Canvasable()
{
    _scene = NULL;
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

void Canvasable::resize(int width, int height)
{
    if(_scene)
    {
        _scene->setWidth(width);
        _scene->getCurrentCamera()->setWidth(width);
        _width = width;
        _scene->setHeight(height);
        _scene->getCurrentCamera()->setHeight(height);
        _height = height;
    }
}

void Canvasable::setScene(std::shared_ptr<Scene> scene){
    _scene = scene;
    _asAScene = true;

    }

void Canvasable::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage){
    _assetsStorage = assetsStorage;
}

void Canvasable::enableScreenSpaceShader(int index){
    if((unsigned int)index < _screenSpaceShader.size()){
        _screenSpaceShader[index] = !_screenSpaceShader[index];
    }else{
        _screenSpaceShader.push_back(false);
    }
}
