#ifndef OBJECT_LIBRARY_H
#define OBJECT_LIBRARY_H

#include <vector>
#include <memory>

#include "model/library.h"

#include "object/light.h"
#include "camera/camera.h"
#include "object/renderableobject.h"
#include "scene/objectnode.h"

class ObjectLibrary
{
  public:
    const Library<Light>&               getLightLibrary() const;
    const Library<Camera>&              getCameraLibrary() const;
    const Library<RenderableObject>&    getRenderableObjectLibrary() const;
    const Library<ObjectNode>&          getObjectNodeLibrary() const;

    void                                addLight(std::shared_ptr<Light> item);
    void                                addCamera(std::shared_ptr<Camera> item);
    void                                addRenderableObject(std::shared_ptr<RenderableObject> item);
    void                                addObjectNode(std::shared_ptr<ObjectNode> item);

    bool                                setCurrentLight(std::shared_ptr<Light> item);
    bool                                setCurrentCamera(std::shared_ptr<Camera> item);
    bool                                setCurrentRenderableObject(std::shared_ptr<RenderableObject> item);
    bool                                setCurrentObjectNode(std::shared_ptr<ObjectNode> item);

  private:
    Library<Light>                      _lights;
    Library<Camera>                     _cameras;
    Library<RenderableObject>           _renderableObjects;
    Library<ObjectNode>                 _objectNodes;
};

#endif // OBJECT_LIBRARY_H
