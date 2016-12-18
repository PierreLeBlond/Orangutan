#ifndef CANVASABLE_H
#define CANVASABLE_H

#include "scene/scene.h"

class Canvasable
{
  public:
                                                Canvasable(GLuint width = 600, GLuint height = 400);
    virtual                                     ~Canvasable() = 0;

    virtual void                                resize(int width, int height);

    void                                        setScene(std::shared_ptr<Scene> scene);
    void                                        setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

    void                                        enableScreenSpaceShader(int index);

  protected:

    std::shared_ptr<AssetsStorage>              _assetsStorage;

    std::shared_ptr<Scene>                      _scene;
    GLuint                                      _width;
    GLuint                                      _height;

    bool                                        _asAScene;

    std::vector<bool>                           _screenSpaceShader;
    bool                                        _mouseIsPressed;
};

#endif // CANVASABLE_H
