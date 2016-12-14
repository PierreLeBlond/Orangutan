#ifndef SCENE_H
#define SCENE_H

#include "object/renderableobject.h"
#include "object/camera.h"

#include "scene/objectnode.h"

#include "scene/assetsstorage.h"

#include <memory>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>


class Scene
{
public:
                                    Scene(std::shared_ptr<AssetsStorage> assetsStorage,
                                         int width = 600,
                                          int height = 400);

    void                            setWidth(int width);
    void                            setHeight(int height);

    void                            setSkybox(int index);

    void                            draw() const;

    void                            setIsReady(bool isReady);
    bool                            isReady() const;

    std::shared_ptr<Camera>         getCurrentCamera();
    std::shared_ptr<Object>         getCurrentObject();
private:

    std::shared_ptr<AssetsStorage>              _assetsStorage;

    GLuint                                      _width;
    GLuint                                      _height;

    std::shared_ptr<Object>                     _currentObject;
    std::shared_ptr<Camera>                     _currentCamera;
    std::shared_ptr<RenderableObject>           _skyBox;

    std::shared_ptr<ObjectNode>                 _sceneTree;

    std::vector<std::shared_ptr<Light>>         _lights;

    bool                                        _isReady;
};

#endif // SCENE_H
