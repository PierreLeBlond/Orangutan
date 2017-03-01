#ifndef OBJECTSFACTORY_H
#define OBJECTSFACTORY_H

#include "model/universe.h"

#include <vector>
#include <memory>

class ObjectsFactory
{
public:

                                            ObjectsFactory(const ObjectsFactory&) = delete;
                                            ObjectsFactory(ObjectsFactory&&) = delete;


    ObjectsFactory&                          operator=(const ObjectsFactory&) = delete;
    ObjectsFactory&                          operator=(ObjectsFactory&&) = delete;

    static ObjectsFactory&                   instance();

    static std::shared_ptr<RenderableObject> createRenderableObject(const Universe& universe,
                                                                   const std::string& name,
                                                                   const Material& material,
                                                                   int meshId,
                                                                   int shaderStrategyId,
                                                                   int textureId,
                                                                   int cubeMapId);

private:
                                            ObjectsFactory(){};
                                            ~ObjectsFactory(){};

    static ObjectsFactory                    _instance;
};

#endif // OBJECTSFACTORY_H
