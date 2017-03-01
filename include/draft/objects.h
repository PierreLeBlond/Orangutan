#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <memory>

#include "object/renderableobject.h"
#include "object/light.h"
#include "camera/camera.h"

class Objects
{
public:
    const Library<Light>&             getLightLibrary() const;
    const Library<Camera>&            getCameraLibrary() const;
    const Library<RenderableObject>&  getRenderableObjectLibrary() const;

    void                              addLight(std::shared_ptr<Light> light);
    void                              addCamera(std::shared_ptr<Camera> camera);
    void                              addRenderableObject(std::shared_ptr<RenderableObject> renderableObject);

private:
    Library<Light>                    _lights;
    Library<Camera>                   _cameras;
    Library<RenderableObject>         _renderableObjects;
};

#endif // OBJECTS_H
