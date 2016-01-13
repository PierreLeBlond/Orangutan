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
                                                    Scene(std::shared_ptr<AssetsStorage> assetsStorage);

    void                                            draw() const;
    void                                            setIsReady(bool isReady);
    bool                                            isReady() const;

    std::shared_ptr<Camera>                         getCurrentCamera();
    std::shared_ptr<Transformable>                  getCurrentTransformable();
private:

    std::shared_ptr<Renderable>                     _currentRenderable;
    std::shared_ptr<Light>                          _currentLight;
    std::shared_ptr<Camera>                         _currentCamera;
    std::shared_ptr<SceneNode>                      _currentSceneNode;

    std::shared_ptr<SceneNode>                      _sceneTree;

    std::vector<std::shared_ptr<LightNode>>         _lightNodes;

    std::shared_ptr<AssetsStorage>                  _assetsStorage;

    bool                                            _isReady;

};

#endif // SCENE_H
