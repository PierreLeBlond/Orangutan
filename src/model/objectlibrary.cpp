#include "model/objectlibrary.h"

const Library<Light>& ObjectLibrary::getLightLibrary() const
{
    return _lights;
}

const Library<Camera>& ObjectLibrary::getCameraLibrary() const
{
    return _cameras;
}

const Library<RenderableObject>& ObjectLibrary::getRenderableObjectLibrary() const
{
    return _renderableObjects;
}

const Library<ObjectNode>& ObjectLibrary::getObjectNodeLibrary() const
{
    return _objectNodes;
}

void ObjectLibrary::addLight(std::shared_ptr<Light> item)
{
    _lights.addItem(item);
}

void ObjectLibrary::addCamera(std::shared_ptr<Camera> item)
{
    _cameras.addItem(item);
}

void ObjectLibrary::addRenderableObject(std::shared_ptr<RenderableObject> item)
{
    _renderableObjects.addItem(item);
}

void ObjectLibrary::addObjectNode(std::shared_ptr<ObjectNode> item)
{
    _objectNodes.addItem(item);
}

bool ObjectLibrary::setCurrentLight(std::shared_ptr<Light> item)
{
    return _lights.setCurrentItemByValue(item);
}

bool ObjectLibrary::setCurrentCamera(std::shared_ptr<Camera> item)
{
    return _cameras.setCurrentItemByValue(item);
}

bool ObjectLibrary::setCurrentRenderableObject(std::shared_ptr<RenderableObject> item)
{
    return _renderableObjects.setCurrentItemByValue(item);
}

bool ObjectLibrary::setCurrentObjectNode(std::shared_ptr<ObjectNode> item)
{
    return _objectNodes.setCurrentItemByValue(item);
}
