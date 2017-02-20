#include "model/assets.h"

const std::vector<std::shared_ptr<Mesh> > &Assets::getMeshs() const {
    return _meshs;
}

const std::vector<std::shared_ptr<DDTexture> > &Assets::getTextures() const {
    return _textures;
}

const std::vector<std::shared_ptr<CubeTexture> > &Assets::getCubeMapTextures() const {
    return _cubeMapTextures;
}


const std::vector<std::shared_ptr<ShaderWrapper>>& Assets::getShaderWrappers() const{
    return _shaderWrappers;
}

const std::vector<std::shared_ptr<const ShaderStrategy>>& Assets::getShaderStrategies() const {
    return _shaderStrategies;
}

const std::vector<std::shared_ptr<const ShaderStrategy>>& Assets::getScreenSpaceShaderStrategies() const {
    return _screenSpaceShaderStrategies;
}

int Assets::getNumberOfMeshs() const {
    return (int) _meshs.size();
}

int Assets::getNumberOfTextures() const {
    return (int) _textures.size();
}

int Assets::getNumberOfCubeMapTextures() const {
    return (int) _cubeMapTextures.size();
}

int Assets::getNumberOfShaderWrappers() const{
    return (int) _shaderWrappers.size();
}

int Assets::getNumberOfShaderStrategies() const {
    return (int) _shaderStrategies.size();
}

int Assets::getNumberOfScreenSpaceShaderStrategies() const {
    return (int) _screenSpaceShaderStrategies.size();
}

std::shared_ptr<Mesh> Assets::getMesh(int index) const{
    return _meshs.at(index);
}

std::shared_ptr<DDTexture> Assets::getTexture(int index) const{
    return _textures.at(index);
}

std::shared_ptr<CubeTexture> Assets::getCubeMapTexture(int index) const{
    return _cubeMapTextures.at(index);
}

std::shared_ptr<ShaderWrapper> Assets::getShaderWrapper(int index) const{
    return _shaderWrappers.at(index);
}

std::shared_ptr<const ShaderStrategy> Assets::getShaderStrategy(int index) const{
    return _shaderStrategies.at(index);
}

std::shared_ptr<const ShaderStrategy> Assets::getScreenSpaceShaderStrategy(int index) const{
    return _screenSpaceShaderStrategies.at(index);
}

void Assets::addMesh(std::shared_ptr<Mesh> mesh){
    _meshs.push_back(mesh);
}

void Assets::addTexture(std::shared_ptr<DDTexture> texture){
    _textures.push_back(texture);
}

void Assets::addCubeMapTexture(std::shared_ptr<CubeTexture> cubeMapTexture){
    _cubeMapTextures.push_back(cubeMapTexture);
}

void Assets::addShaderWrapper(std::shared_ptr<ShaderWrapper> shaderWrapper){
    _shaderWrappers.push_back(shaderWrapper);
}

void Assets::addShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy){
    _shaderStrategies.push_back(shaderStrategy);
}

void Assets::addScreenSpaceShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy){
    _screenSpaceShaderStrategies.push_back(shaderStrategy);
}
