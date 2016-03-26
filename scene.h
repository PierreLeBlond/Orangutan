#ifndef SCENE_H
#define SCENE_H

#include "renderable.h"
#include "renderablenode.h"
#include "camera.h"
#include "cameranode.h"
#include "assetsstorage.h"

#include <memory>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>


class Scene
{
public:
                                                    Scene(std::shared_ptr<AssetsStorage> assetsStorage, int width = 600, int height = 400);

    void                                            setWidth(int width);
    void                                            setHeight(int height);

    void                                            setSkybox(int index);

    void                                            draw() const;
    void                                            drawScreenSpace() const;
    void                                            setIsReady(bool isReady);
    bool                                            isReady() const;

    std::shared_ptr<Camera>                         getCurrentCamera();
    std::shared_ptr<Transformable>                  getCurrentTransformable();
    std::shared_ptr<Materialable>                   getCurrentMaterialable();
    std::shared_ptr<Renderer>                     getCurrentRenderable();
    std::shared_ptr<Renderer>                     getScreenSpaceRenderable();
private:

    GLuint                                          _width;
    GLuint                                          _height;

    std::shared_ptr<Renderer>                     _currentRenderable;
    std::shared_ptr<Renderer>                     _screenSpaceRenderable;

    std::shared_ptr<Light>                          _currentLight;
    std::shared_ptr<Camera>                         _currentCamera;
    std::shared_ptr<SceneNode>                      _currentSceneNode;

    std::shared_ptr<Renderer>                     _skyBox;

    std::shared_ptr<SceneNode>                      _sceneTree;

    std::vector<std::shared_ptr<LightNode>>         _lightNodes;

    std::shared_ptr<AssetsStorage>                  _assetsStorage;

    bool                                            _isReady;

};

#endif // SCENE_H
