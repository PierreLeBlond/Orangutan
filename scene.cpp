#include "scene.h"

Scene::Scene(std::shared_ptr<AssetsStorage> assetsStorage) : _assetsStorage(assetsStorage)
{
    auto cubeMap = std::make_shared<Renderable>();
    cubeMap->setMesh(_assetsStorage->getMesh(0));
    cubeMap->CreateCubeMap();
    cubeMap->setShaderStrategy(_assetsStorage->getShaderStrategy(1));
    cubeMap->fillInVBO();
    cubeMap->createVertexArrayObject();
    cubeMap->setXScale(100);
    cubeMap->setYScale(100);
    cubeMap->setZScale(100);

    auto cubeMapNode = std::make_shared<RenderableNode>();
    cubeMapNode->addRenderable(cubeMap);

    _sceneTree = cubeMapNode;

    _currentRenderable = std::make_shared<Renderable>();
    _currentRenderable->setMesh(_assetsStorage->getMesh(0));

    _currentRenderable->setShaderStrategy(_assetsStorage->getShaderStrategy(0));
    _currentRenderable->setKa(0.5f);
    _currentRenderable->setColor(QColor(255, 0, 0));
    _currentRenderable->setColorMap(_assetsStorage->getTexture(0));
    _currentRenderable->fillInVBO();
    _currentRenderable->createVertexArrayObject();
    _currentRenderable->setZPos(-10);

    auto node = std::make_shared<RenderableNode>();
    node->addRenderable(_currentRenderable);

    cubeMapNode->addChild(node);

    auto light = std::make_shared<Light>();
    light->setYPos(10);

    auto lightNode = std::make_shared<LightNode>();
    lightNode->setLight(light);

    _sceneTree->addChild(lightNode);

    _currentLight = light;
    _lightNodes.push_back(lightNode);

    _currentCamera = std::make_shared<Camera>(600, 400);

    auto cameraNode = std::make_shared<CameraNode>();
    cameraNode->setCamera(_currentCamera);

    _sceneTree->addChild(cameraNode);




}

void Scene::draw() const{
    glm::vec3 vec(1.0f);
    _sceneTree->display(_currentCamera->getView(vec), _currentCamera->getPerspectiveProjection(), _lightNodes);
}

void Scene::setIsReady(bool isReady){
    _isReady = isReady;
}

bool Scene::isReady() const{
    return _isReady;
}

std::shared_ptr<Camera> Scene::getCurrentCamera(){
    return _currentCamera;
}

std::shared_ptr<Transformable> Scene::getCurrentTransformable(){
    return _currentRenderable;
}

