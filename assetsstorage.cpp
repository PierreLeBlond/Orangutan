#include "assetsstorage.h"

AssetsStorage::AssetsStorage()
{

}

AssetsStorage::~AssetsStorage()
{
    _meshs.clear();
    _textures.clear();
    _shaderStrategies.clear();
}

const std::vector<std::shared_ptr<Mesh> > &AssetsStorage::getMeshs() const {
    return _meshs;
}

const std::vector<std::shared_ptr<Texture> > &AssetsStorage::getTextures() const {
    return _textures;
}

const std::vector<std::shared_ptr<Texture> > &AssetsStorage::getCubeMapTextures() const {
    return _cubeMapTextures;
}


const std::vector<const ShaderProgram*>& AssetsStorage::getShaderPrograms() const{
    return _shaderPrograms;
}

const std::vector<const ShaderStrategy*>& AssetsStorage::getShaderStrategies() const {
    return _shaderStrategies;
}

const std::vector<const ShaderStrategy*>& AssetsStorage::getScreenSpaceShaderStrategies() const {
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

int AssetsStorage::getNumberOfShaderPrograms() const{
    return (int) _shaderStrategies.size();
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

std::shared_ptr<Texture> AssetsStorage::getTexture(int index) const{
    return _textures.at(index);
}

std::shared_ptr<Texture> AssetsStorage::getCubeMapTexture(int index) const{
    return _cubeMapTextures.at(index);
}

const ShaderProgram& AssetsStorage::getShaderProgram(int index) const{
    return *_shaderPrograms.at(index);
}

const ShaderStrategy* AssetsStorage::getShaderStrategy(int index) const{
    return _shaderStrategies.at(index);
}

const ShaderStrategy *AssetsStorage::getScreenSpaceShaderStrategy(int index) const{
    return _screenSpaceShaderStrategies.at(index);
}

void AssetsStorage::addMesh(std::shared_ptr<Mesh> mesh){
    _meshs.push_back(mesh);
}

void AssetsStorage::addTexture(std::shared_ptr<Texture> texture){
    _textures.push_back(texture);
}

void AssetsStorage::addCubeMapTexture(std::shared_ptr<Texture> cubeMapTexture){
    _cubeMapTextures.push_back(cubeMapTexture);
}

void AssetsStorage::addShaderProgram(const ShaderProgram *shaderProgram){
    _shaderPrograms.push_back(shaderProgram);
}

void AssetsStorage::addShaderStrategy(const ShaderStrategy *shaderStrategy){
    _shaderStrategies.push_back(shaderStrategy);
}

void AssetsStorage::addScreenSpaceShaderStrategy(const ShaderStrategy *shaderStrategy){
    _screenSpaceShaderStrategies.push_back(shaderStrategy);
}




