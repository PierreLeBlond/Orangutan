#include "scene/assetsfactory.h"

AssetsFactory::AssetsFactory(std::shared_ptr<AssetsStorage> assetsStorage) : _assetsStorage(assetsStorage)
{
    std::shared_ptr<Mesh> square = Mesh::createSquare();
    _assetsStorage->addMesh(square);

    std::shared_ptr<Mesh> cube = Mesh::createCube(2, "myCube");
    _assetsStorage->addMesh(cube);

    std::shared_ptr<Mesh> sphere = Mesh::createSphere(4, "mySphere");
    _assetsStorage->addMesh(sphere);
}

AssetsFactory::~AssetsFactory()
{
}

int AssetsFactory::importMeshs(const char *filename, const char *name){
    std::vector<std::shared_ptr<Mesh>> meshs = Parseur::parseObj(filename);

    for(unsigned int i = 0;i < meshs.size();i++) {
        meshs[i]->setName(name);
        _assetsStorage->addMesh(meshs[i]);
    }
    return _assetsStorage->getNumberOfMeshs() - meshs.size();
}

int AssetsFactory::importTexture(const char *filename, const char *name){
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename, name);
    texture->setName(name);
    _assetsStorage->addTexture(texture);
    return _assetsStorage->getNumberOfTextures() - 1;
}

int AssetsFactory::importCubeMapTexture(const char *filename, const char *name){
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->loadCubeMap(filename);
    texture->setName(name);
    _assetsStorage->addCubeMapTexture(texture);
    return _assetsStorage->getNumberOfCubeMapTextures() - 1;
}

int AssetsFactory::importShader(const char *vertexFilename, const char *fragmentFilename, const char *geometryFilename){
    std::shared_ptr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>();
    shaderProgram->initShader(vertexFilename, fragmentFilename, geometryFilename);
    _assetsStorage->addShaderProgram(shaderProgram);
    return _assetsStorage->getNumberOfShaderPrograms() - 1;
}

int AssetsFactory::createNewShaderStrategy(int shaderId, const char *name){
    int id = _assetsStorage->getNumberOfShaderStrategies();
    std::shared_ptr<ShaderStrategy> strategy;
    strategy = std::make_shared<ShaderStrategy>(name);
    strategy->setShaderProgram(_assetsStorage->getShaderProgram(shaderId));
    strategy->initAttribute();
    _assetsStorage->addShaderStrategy(strategy);
    return id;
}

int AssetsFactory::createNewScreenSpaceShaderStrategy(int type, int shaderId, const char *name){
    /*int id = _assetsStorage->getNumberOfScreenSpaceShaderStrategies();
    std::shared_ptr<ShaderStrategy> strategy;
    switch(type){
    case EDGEFILTER :
        strategy = std::make_shared<EdgeFilterStrategy>(name);
        strategy->setShaderProgram(_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        _assetsStorage->addScreenSpaceShaderStrategy(strategy);
        break;
    case GAUSSIANBLURFILTER :
        strategy = std::make_shared<GaussianBlurFilterStrategy>(name);
        strategy->setShaderProgram(_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        _assetsStorage->addScreenSpaceShaderStrategy(strategy);
    default :
        id = -1;
        break;
    }
    return id;*/
    return -1;
}
