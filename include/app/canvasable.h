#ifndef CANVASABLE_H
#define CANVASABLE_H

#include "scene/scene.h"

class Canvasable
{
  public:
                                                Canvasable(unsigned int width = 600, unsigned int height = 400);
    virtual                                     ~Canvasable();

    virtual void                                resize(int width, int height);

    void                                        setScene(std::shared_ptr<Scene> scene);
    void                                        setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

    void                                        enableScreenSpaceShader(int index);

  protected:

    std::shared_ptr<AssetsStorage>              _assetsStorage;

    std::shared_ptr<Scene>                      _scene;
    unsigned int                                      _width;
    unsigned int                                      _height;

    bool                                        _asAScene;

    std::vector<bool>                           _screenSpaceShader;
    bool                                        _mouseIsPressed;
};

#endif // CANVASABLE_H
