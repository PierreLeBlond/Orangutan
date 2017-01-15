#include "app/objecttoolable.h"

ObjectToolable::ObjectToolable()
{
}

ObjectToolable::~ObjectToolable()
{
}

void ObjectToolable::setCurrentObject(std::shared_ptr<RenderableObject> object)
{
    _object = object;
}

void ObjectToolable::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage)
{
    _assetsStorage = assetsStorage;
}

void ObjectToolable::setMap(int id)
{
    if(_object)
        _object->setColorMapId(_assetsStorage->getTexture(id)->getId());
}

void ObjectToolable::setMaterial(int id)
{
    if(_object)
        _object->setShaderStrategy(_assetsStorage->getShaderStrategy(id));
}



