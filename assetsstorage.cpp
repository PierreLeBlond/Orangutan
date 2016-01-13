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

const std::vector<const Mesh>& AssetsStorage::getMeshs() const {
    return _meshs;
}

const std::vector<GLuint>& AssetsStorage::getTextures() const {
    return _textures;
}

const std::vector<const ShaderProgram*>& AssetsStorage::getShaderPrograms() const{
    return _shaderPrograms;
}

const std::vector<const ShaderStrategy*>& AssetsStorage::getShaderStrategies() const {
    return _shaderStrategies;
}

int AssetsStorage::getNumberOfMeshs() const {
    return (int) _meshs.size();
}

int AssetsStorage::getNumberOfTextures() const {
    return (int) _textures.size();
}

int AssetsStorage::getNumberOfShaderPrograms() const{
    return (int) _shaderStrategies.size();
}

int AssetsStorage::getNumberOfShaderStrategies() const {
    return (int) _shaderStrategies.size();
}

const Mesh& AssetsStorage::getMesh(int index) const{
    return _meshs.at(index);
}

GLuint AssetsStorage::getTexture(int index) const{
    return _textures.at(index);
}

const ShaderProgram& AssetsStorage::getShaderProgram(int index) const{
    return *_shaderPrograms.at(index);
}

const ShaderStrategy* AssetsStorage::getShaderStrategy(int index) const{
    return _shaderStrategies.at(index);
}

void AssetsStorage::addMesh(const Mesh mesh){
    _meshs.push_back(mesh);
}

void AssetsStorage::addTexture(GLuint texture){
    _textures.push_back(texture);
}

void AssetsStorage::addShaderProgram(const ShaderProgram *shaderProgram){
    _shaderPrograms.push_back(shaderProgram);
}

void AssetsStorage::addShaderStrategy(const ShaderStrategy *shaderStrategy){
    _shaderStrategies.push_back(shaderStrategy);
}




