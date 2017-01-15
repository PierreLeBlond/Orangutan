#ifndef OBJECT_TOOLABLE_H
#define OBJECT_TOOLABLE_H

#include <memory>

#include "object/renderableobject.h"
#include "scene/assetsstorage.h"

class ObjectToolable
{
  public:
                                                ObjectToolable();
    virtual                                     ~ObjectToolable();

    void                                        setCurrentObject(std::shared_ptr<RenderableObject> object);
    void                                        setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

    void                                        setMap(int id);
    void                                        setMaterial(int id);

  protected:

    std::shared_ptr<RenderableObject>           _object;
    std::shared_ptr<AssetsStorage>              _assetsStorage;
};

#endif // OBJECT_TOOLABLE_H
