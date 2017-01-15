#ifndef MAIN_TOOLABLE_H
#define MAIN_TOOLABLE_H

#include <memory>

#include "object/renderableobject.h"
#include "scene/assetsstorage.h"
#include "scene/scene.h"

class MainToolable
{
  public:
                                                MainToolable();
    virtual                                     ~MainToolable();

    void                                        setCurrentObject(std::shared_ptr<RenderableObject> object);
    void                                        setScene(std::shared_ptr<Scene> scene);
    void                                        setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

    void                                        setSkybox(int id);

  protected:

    std::shared_ptr<RenderableObject>           _object;
    std::shared_ptr<AssetsStorage>              _assetsStorage;
    std::shared_ptr<Scene>                      _scene;
};

#endif // MAIN_TOOLABLE_H
