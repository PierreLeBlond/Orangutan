#ifndef INVENTORY_H
#define INVENTORY_H

#include "object/renderableobject.h"
#include "object/lights.h"
#include "camera/camera.h"

#include "scene/scene.h"
#include "scene/assetsstorage.h"

#include <memory>

class Scene
{
public:
                                    Scene(std::shared_ptr<AssetsStorage> assetsStorage,
                                         int width = 600,
                                          int height = 400);

    void                            setWidth(int width);
    void                            setHeight(int height);

    void                            setSkybox(int index);

    void                            update();
    void                            animate();

    void                            setIsReady(bool isReady);
    bool                            isReady() const;

    const std::shared_ptr<
        ObjectNode>&                getSceneTree() const;

    const std::shared_ptr<Camera>&  getCurrentCamera() const;
    void                            setCurrentCamera(std::shared_ptr<Camera> camera);

    const std::vector<
        std::shared_ptr<Light>>&    getLights() const;
    const std::vector<
        std::shared_ptr<Camera>>&   getCameras() const;

    const std::shared_ptr<
        RenderableObject>&          getCurrentRenderableObject() const;
private:

    std::shared_ptr<AssetsStorage>              _assetsStorage;

    unsigned int                                _width;
    unsigned int                                _height;

    std::shared_ptr<RenderableObject>           _currentRenderableObject;
    std::shared_ptr<Camera>                     _currentCamera;
    std::shared_ptr<RenderableObject>           _skyBox;

    std::shared_ptr<ObjectNode>                 _sceneTree;

    std::vector<
        std::shared_ptr<RenderableObject>>      _renderableObjects;
    std::vector<std::shared_ptr<Light>>         _lights;
    std::vector<std::shared_ptr<Camera>>        _cameras;

    bool                                        _isReady;
};

#endif // INVENTORY_H
