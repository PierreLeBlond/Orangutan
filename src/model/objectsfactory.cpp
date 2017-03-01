#include "model/objectsfactory.h"

#include <iostream>

ObjectsFactory ObjectsFactory::_instance;

ObjectsFactory& ObjectsFactory::instance()
{
    return _instance;
}

std::shared_ptr<RenderableObject> ObjectsFactory::createRenderableObject(const Universe& universe,
                                                                         const std::string& name,
                                                                         const Material& material,
                                                                         int meshId,
                                                                         int shaderStrategyId,
                                                                         int textureId,
                                                                         int cubeMapId)
{
    std::shared_ptr<RenderableObject> object = std::make_shared<RenderableObject>(name);

    if(meshId > -1)
    {
        std::shared_ptr<Mesh> mesh;
        if(universe.getMeshLibrary().getItemById(meshId, mesh))
            object->setMesh(mesh);
        else
            std::cout << "couldn't find mesh at id " << meshId << std::endl;
    }

    object->addMaterial(material);

    if(shaderStrategyId > -1)
    {
        std::shared_ptr<ShaderStrategy> shaderStrategy;
        if(universe.getShaderStrategyLibrary().getItemById(shaderStrategyId, shaderStrategy))
        {
            if(shaderStrategy.get() == nullptr)
                std::cout << "Gnah" << std::endl;
            object->setShaderStrategy(shaderStrategy);
        }
        else
            std::cout << "Couldn't find shader strategy at id " << shaderStrategyId << std::endl;
    }

    if(textureId > -1)
    {
        std::shared_ptr<DDTexture> texture;
        if(universe.getTextureLibrary().getItemById(textureId, texture))
            object->setTexture("colorMap", texture);
    }

    if(cubeMapId > -1)
    {
        std::shared_ptr<CubeTexture> cubeTexture;
        if(universe.getCubeTextureLibrary().getItemById(cubeMapId, cubeTexture))
            object->setCubeTexture("cubeMap", cubeTexture);
    }

    return object;
}

