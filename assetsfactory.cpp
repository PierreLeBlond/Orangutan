#include "assetsfactory.h"

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

int AssetsFactory::importMeshs(const char *filename){
    std::vector<std::shared_ptr<Mesh>> meshs = Parseur::parseObj(filename);
    for(unsigned int i = 0;i < meshs.size();i++) {
        _assetsStorage->addMesh(meshs[i]);
    }
    return _assetsStorage->getNumberOfMeshs() - meshs.size();
}

int AssetsFactory::importTexture(const char *filename, const char *name){
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename);
    texture->setName(std::string(name));
    _assetsStorage->addTexture(texture);
    return _assetsStorage->getNumberOfTextures() - 1;
}

int AssetsFactory::importCubeMapTexture(const char *filename, const char *name){
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->setName(std::string(name));
    texture->loadCubeMap(filename);
    _assetsStorage->addCubeMapTexture(texture);
    return _assetsStorage->getNumberOfCubeMapTextures() - 1;
}

int AssetsFactory::importShader(const char *vertexFilename, const char *fragmentFilename, const char *geometryFilename){
    ShaderProgram* shaderProgram = new ShaderProgram;
    shaderProgram->initShader(vertexFilename, fragmentFilename, geometryFilename);
    _assetsStorage->addShaderProgram(shaderProgram);
    return _assetsStorage->getNumberOfShaderPrograms() - 1;
}

int AssetsFactory::createNewShaderStrategy(int type, int shaderId, const char *name){
    int id = _assetsStorage->getNumberOfShaderStrategies();
    ShaderStrategy* strategy;
    switch(type){
    case GOURAUD :
        strategy = new GouraudStrategy;
        strategy->setShaderProgram(&_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        strategy->initUniformLocation();
        strategy->setName(std::string(name));
        _assetsStorage->addShaderStrategy(strategy);
        break;
    case TOON :
        strategy = new ToonStrategy;
        strategy->setShaderProgram(&_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        strategy->initUniformLocation();
        strategy->setName(std::string(name));
        _assetsStorage->addShaderStrategy(strategy);
       break;
   case ENVIRONMENTMAP :
        strategy = new EnvironmentStrategy;
        strategy->setShaderProgram(&_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        strategy->initUniformLocation();
        strategy->setName(std::string(name));
        _assetsStorage->addShaderStrategy(strategy);
      break;
    case SKYBOX :
        strategy = new SkyboxStrategy;
        strategy->setShaderProgram(&_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        strategy->initUniformLocation();
        strategy->setName(std::string(name));
        _assetsStorage->addShaderStrategy(strategy);
        break;
    default :
        id = -1;
        break;
    }
    return id;
}

int AssetsFactory::createNewScreenSpaceShaderStrategy(int type, int shaderId, const char *name){
    int id = _assetsStorage->getNumberOfScreenSpaceShaderStrategies();
    ShaderStrategy* strategy;
    switch(type){
    case EDGEFILTER :
        strategy = new EdgeFilterStrategy;
        strategy->setShaderProgram(&_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        strategy->initUniformLocation();
        strategy->setName(std::string(name));
        _assetsStorage->addScreenSpaceShaderStrategy(strategy);
        break;
    case GAUSSIANBLURFILTER :
        strategy = new GaussianBlurFilterStrategy;
        strategy->setShaderProgram(&_assetsStorage->getShaderProgram(shaderId));
        strategy->initAttribute();
        strategy->initUniformLocation();
        strategy->setName(std::string(name));
        _assetsStorage->addScreenSpaceShaderStrategy(strategy);
    default :
        id = -1;
        break;
    }
    return id;
}


