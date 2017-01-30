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

void ObjectToolable::setShaderStrategy(int id)
{
    if(_object)
        _object->setShaderStrategy(_assetsStorage->getShaderStrategy(id));
}



