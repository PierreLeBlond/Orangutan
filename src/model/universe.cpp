#include "model/universe.h"

const Library<Mesh>& Universe::getMeshLibrary() const
{
    return _meshs;
}

const Library<DDTexture>& Universe::getTextureLibrary() const
{
    return _textures;
}

const Library<CubeTexture>& Universe::getCubeTextureLibrary() const
{
    return _cubeTextures;
}

const Library<ShaderWrapper>& Universe::getShaderWrapperLibrary() const
{
    return _shaderWrappers;
}

const Library<ShaderStrategy>& Universe::getShaderStrategyLibrary() const
{
    return _shaderStrategies;
}

const Library<Scene>& Universe::getSceneLibrary() const
{
    return _scenes;
}

void Universe::addMesh(std::shared_ptr<Mesh> item)
{
    _meshs.addItem(item);
}

void Universe::addTexture(std::shared_ptr<DDTexture> item)
{
    _textures.addItem(item);
}

void Universe::addCubeTexture(std::shared_ptr<CubeTexture> item)
{
    _cubeTextures.addItem(item);
}

void Universe::addShaderWrapper(std::shared_ptr<ShaderWrapper> item)
{
    _shaderWrappers.addItem(item);
}

void Universe::addShaderStrategy(std::shared_ptr<ShaderStrategy> item)
{
    _shaderStrategies.addItem(item);
}

void Universe::addScene(std::shared_ptr<Scene> item)
{
    _scenes.addItem(item);
}

bool Universe::setCurrentScene(std::shared_ptr<Scene> item)
{
    return _scenes.setCurrentItemByValue(item);
}
