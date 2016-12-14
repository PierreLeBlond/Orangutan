#include "scene/scene.h"
#include "core/debug.h"

Scene::Scene(std::shared_ptr<AssetsStorage> assetsStorage, int width, int height) :
    _assetsStorage(assetsStorage), _width(width), _height(height)
{
    auto universe = std::make_shared<Object>();
    auto universeNode = std::make_shared<ObjectNode>();
    universeNode->setObject(universe);

    _sceneTree = universeNode;

    //Cameras
    _currentCamera = std::make_shared<Camera>(_width, _height);

    auto cameraNode = std::make_shared<ObjectNode>();
    cameraNode->setObject(_currentCamera);

    //_sceneTree->addChild(cameraNode);

    //CubeMap
    std::shared_ptr<RenderableObject> cubeMap = std::make_shared<RenderableObject>();
    cubeMap->setMesh(_assetsStorage->getMesh(1));
    cubeMap->setCubeMapId(_assetsStorage->getCubeMapTexture(1)->getId());
    cubeMap->setShaderStrategy(_assetsStorage->getShaderStrategy(1));
    cubeMap->fillInVBO();
    cubeMap->createVertexArrayObject();

    _skyBox = cubeMap;
    //_currentCamera->setSkybox(_skyBox);

    auto cubeMapNode = std::make_shared<ObjectNode>();
    cubeMapNode->setXScale(100);
    cubeMapNode->setYScale(100);
    cubeMapNode->setZScale(100);
    cubeMapNode->setObject(cubeMap);

    _sceneTree->addChild(cubeMapNode);

    std::shared_ptr<RenderableObject> object = std::make_shared<RenderableObject>();
    _currentObject = object;
    object->setMesh(_assetsStorage->getMesh(4));

    object->setShaderStrategy(_assetsStorage->getShaderStrategy(4));
    object->setKa(0.5f);
    object->setColorMapId(_assetsStorage->getTexture(2)->getId());
    object->setCubeMapId(_assetsStorage->getCubeMapTexture(1)->getId());
    object->fillInVBO();
    object->createVertexArrayObject();

    auto node = std::make_shared<ObjectNode>();
    node->setObject(object);

    _sceneTree->addChild(node);

    //Lights
    auto light = std::make_shared<Light>();
    light->setXPos(10);
    light->setZPos(10);

    auto lightNode = std::make_shared<ObjectNode>();
    lightNode->setObject(light);

    _sceneTree->addChild(lightNode);

    _lights.push_back(light);

    /*_screenSpaceObject = std::make_shared<Renderer>();
    _screenSpaceObject->setMesh(_assetsStorage->getMesh(0));

    _screenSpaceObject->setShaderStrategy(_assetsStorage->getScreenSpaceShaderStrategy(0));
    _screenSpaceObject->fillInVBO();
    _screenSpaceObject->createVertexArrayObject();*/
}

void Scene::setSkybox(int index){
    _skyBox->setCubeMapId(index);
    //TO DO : apply to each object of the scene
    //_currentObject->setCubeMapId(index);
}

void Scene::setWidth(int width){
    _width = width;
}

void Scene::setHeight(int height){
    _height = height;
}

void Scene::draw() const{
    _currentCamera->update();
    glm::mat4 mat(1.0);
    _sceneTree->updateScene(mat);
    _sceneTree->displayScene(_currentCamera->getView(),
                             _currentCamera->computePerspectiveProjection(),
                             _lights);
}

/*void Scene::drawScreenSpace() const{
    _screenSpaceObject->draw(glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), _ObjectNodes);
}*/

void Scene::setIsReady(bool isReady){
    _isReady = isReady;
}

bool Scene::isReady() const{
    return _isReady;
}

std::shared_ptr<Camera> Scene::getCurrentCamera(){
    return _currentCamera;
}

std::shared_ptr<Object> Scene::getCurrentObject(){
    return _currentObject;
}
