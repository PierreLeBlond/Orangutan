#ifndef SCREENABLE_H
#define SCREENABLE_H

#include "scene/assetsfactory.h"
#include "scene/assetsstorage.h"
#include "scene/scene.h"

#include "util/util.h"

class Screenable
{
  public:
                                                    Screenable();
    virtual                                         ~Screenable() = 0;

    virtual void                                    init();

  protected:

    std::shared_ptr<AssetsFactory>          _assetsFactory;
    std::shared_ptr<AssetsStorage>          _assetsStorage;
    std::shared_ptr<Scene>                  _scene;
};

#endif // Screenable_H
