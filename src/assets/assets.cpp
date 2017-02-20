#include "scene/assetsstorage.h"

AssetsStorage::AssetsStorage()
{

}

const std::vector<std::shared_ptr<Mesh> > &AssetsStorage::getMeshs() const {
    return _meshs;
}

const std::vector<std::shared_ptr<DDTexture> > &AssetsStorage::getTextures() const {
    return _textures;
}

const std::vector<std::shared_ptr<CubeTexture> > &AssetsStorage::getCubeMapTextures() const {
    return _cubeMapTextures;
}


const std::vector<std::shared_ptr<ShaderWrapper>>& AssetsStorage::getShaderWrappers() const{
    return _shaderWrappers;
}

const std::vector<std::shared_ptr<const ShaderStrategy>>& AssetsStorage::getShaderStrategies() const {
    return _shaderStrategies;
}

const std::vector<std::shared_ptr<const ShaderStrategy>>& AssetsStorage::getScreenSpaceShaderStrategies() const {
    return _screenSpaceShaderStrategies;
}

int AssetsStorage::getNumberOfMeshs() const {
    return (int) _meshs.size();
}

int AssetsStorage::getNumberOfTextures() const {
    return (int) _textures.size();
}

int AssetsStorage::getNumberOfCubeMapTextures() const {
    return (int) _cubeMapTextures.size();
}

int AssetsStorage::getNumberOfShaderWrappers() const{
    return (int) _shaderWrappers.size();
}

int AssetsStorage::getNumberOfShaderStrategies() const {
    return (int) _shaderStrategies.size();
}

int AssetsStorage::getNumberOfScreenSpaceShaderStrategies() const {
    return (int) _screenSpaceShaderStrategies.size();
}

std::shared_ptr<Mesh> AssetsStorage::getMesh(int index) const{
    return _meshs.at(index);
}

std::shared_ptr<DDTexture> AssetsStorage::getTexture(int index) const{
    return _textures.at(index);
}

std::shared_ptr<CubeTexture> AssetsStorage::getCubeMapTexture(int index) const{
    return _cubeMapTextures.at(index);
}

std::shared_ptr<ShaderWrapper> AssetsStorage::getShaderWrapper(int index) const{
    return _shaderWrappers.at(index);
}

std::shared_ptr<const ShaderStrategy> AssetsStorage::getShaderStrategy(int index) const{
    return _shaderStrategies.at(index);
}

std::shared_ptr<const ShaderStrategy> AssetsStorage::getScreenSpaceShaderStrategy(int index) const{
    return _screenSpaceShaderStrategies.at(index);
}

void AssetsStorage::addMesh(std::shared_ptr<Mesh> mesh){
    _meshs.push_back(mesh);
}

void AssetsStorage::addTexture(std::shared_ptr<DDTexture> texture){
    _textures.push_back(texture);
}

void AssetsStorage::addCubeMapTexture(std::shared_ptr<CubeTexture> cubeMapTexture){
    _cubeMapTextures.push_back(cubeMapTexture);
}

void AssetsStorage::addShaderWrapper(std::shared_ptr<ShaderWrapper> shaderWrapper){
    _shaderWrappers.push_back(shaderWrapper);
}

void AssetsStorage::addShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy){
    _shaderStrategies.push_back(shaderStrategy);
}

void AssetsStorage::addScreenSpaceShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy){
    _screenSpaceShaderStrategies.push_back(shaderStrategy);
}
