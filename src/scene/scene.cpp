#include "scene/scene.h"
#include "core/debug.h"
#include "util/keyboard.h"
#include "camera/trackballcamera.h"
#include "camera/freecamera.h"

Scene::Scene(std::shared_ptr<AssetsStorage> assetsStorage, int width, int height) :
    _assetsStorage(assetsStorage), _width(width), _height(height)
{
    auto universe = std::make_shared<Object>();
    auto universeNode = std::make_shared<ObjectNode>();
    universeNode->setObject(universe);

    _sceneTree = universeNode;

    //Cameras
    std::shared_ptr<TrackBallCamera> trackBallCamera = std::make_shared<TrackBallCamera>(_width, _height);
    _currentCamera = trackBallCamera;
    _cameras.push_back(trackBallCamera);

    std::shared_ptr<FreeCamera> freeCamera = std::make_shared<FreeCamera>(_width, _height);
    _cameras.push_back(freeCamera);

    _sceneTree->addChild(_currentCamera);

    //
    //CubeMap
    std::shared_ptr<RenderableObject> cubeMap = std::make_shared<RenderableObject>("Skybox");
    cubeMap->setMesh(_assetsStorage->getMesh(1));
    cubeMap->addMaterial(MaterialFactory::createSkyboxMaterial());
    cubeMap->setCubeTexture("cubeMap", _assetsStorage->getCubeMapTexture(1));
    cubeMap->setShaderStrategy(_assetsStorage->getShaderStrategy(1));
    cubeMap->fillInVBO();
    cubeMap->initVertexArrayObject();

    cubeMap->setXScale(10);
    cubeMap->setYScale(10);
    cubeMap->setZScale(10);

    _skyBox = cubeMap;

    auto cubeMapNode = std::make_shared<ObjectNode>();
    cubeMapNode->setObject(cubeMap);

    _currentCamera->addChild(cubeMapNode);

    //mozart
    std::shared_ptr<RenderableObject> object = std::make_shared<RenderableObject>("Mozart");
    _currentRenderableObject = object;
    object->setMesh(_assetsStorage->getMesh(4));
    object->setShaderStrategy(_assetsStorage->getShaderStrategy(0));
    object->addMaterial(MaterialFactory::createDefaultMaterial());
    object->setTexture("colorMap", _assetsStorage->getTexture(2));
    object->setCubeTexture("cubeMap", _assetsStorage->getCubeMapTexture(1));
    object->fillInVBO();
    object->initVertexArrayObject();

    auto node = std::make_shared<ObjectNode>();
    node->setObject(object);

    node->setXPos(5);

    _renderableObjects.push_back(object);
    _sceneTree->addChild(node);

    //Minion
    object = std::make_shared<RenderableObject>("Minion");
    object->setMesh(_assetsStorage->getMesh(3));
    object->setShaderStrategy(_assetsStorage->getShaderStrategy(0));
    object->addMaterial(MaterialFactory::createDefaultMaterial());
    object->setTexture("colorMap", _assetsStorage->getTexture(1));
    object->setCubeTexture("cubeMap", _assetsStorage->getCubeMapTexture(1));
    object->fillInVBO();
    object->initVertexArrayObject();

    node = std::make_shared<ObjectNode>();
    node->setObject(object);

    node->setXPos(-5);

    _renderableObjects.push_back(object);
    _sceneTree->addChild(node);

    //Lights
    auto light = std::make_shared<Light>();
    light->setYTranslationBigAxe(5);
    light->setYTranslationSmallAxe(5);
    light->setYTranslationSpeed(0.2);

    auto lightNode = std::make_shared<ObjectNode>();
    lightNode->setObject(light);

    _sceneTree->addChild(lightNode);

    _lights.push_back(light);

    trackBallCamera->setFocus(_currentRenderableObject);

    /*_screenSpaceObject = std::make_shared<Renderer>();
    _screenSpaceObject->setMesh(_assetsStorage->getMesh(0));

    _screenSpaceObject->setShaderStrategy(_assetsStorage->getScreenSpaceShaderStrategy(0));
    _screenSpaceObject->fillInVBO();
    _screenSpaceObject->createVertexArrayObject();*/
}

void Scene::setSkybox(int index){
    //_skyBox->setCubeMapId(index);
    //TO DO : apply to each object of the scene
    //_currentObject->setCubeMapId(index);
}

void Scene::setWidth(int width){
    _width = width;
}

void Scene::setHeight(int height){
    _height = height;
}

void Scene::update()
{
    _currentCamera->update();
    glm::mat4 mat(1.0);
    _sceneTree->updateScene(mat);
}

void Scene::animate() {
    const std::vector<State>& keyboard = Keyboard::instance().getKeyboard();

    for(unsigned int key = 0; key < keyboard.size(); ++key)
    {
        if(keyboard[key] == KEYNDOWN || keyboard[key] == KEYDOWN)
            switch(key)
            {
              case 265:
                getCurrentCamera()->pitch(5.0f);
                break;
              case 264:
                getCurrentCamera()->pitch(-5.0f);
                break;
              case 262:
                getCurrentCamera()->yaw(5.0f);
                break;
              case 263:
                getCurrentCamera()->yaw(-5.0f);
                break;
              case 87:
                getCurrentCamera()->move(FORWARD);
                break;
              case 83:
                getCurrentCamera()->move(BACKWARD);
                break;
              case 65:
                getCurrentCamera()->move(LEFT);
                break;
              case 68:
                getCurrentCamera()->move(RIGHT);
                break;
              case 79:
                getCurrentCamera()->setOrthoProjectionMode();
                break;
              case 80:
                getCurrentCamera()->setPerspectiveProjectionMode();
                break;
              case 56:
                getCurrentRenderableObject()->move(FORWARD);
                break;
              case 50:
                getCurrentRenderableObject()->move(BACKWARD);
                break;
              case 52:
                getCurrentRenderableObject()->move(LEFT);
                break;
              case 54:
                getCurrentRenderableObject()->move(RIGHT);
                break;
              case 57:
                getCurrentRenderableObject()->move(UP);
                break;
              case 51:
                getCurrentRenderableObject()->move(DOWN);
                break;
              case 334:
                getCurrentCamera()->move(UP);
                break;
              case 333:
                getCurrentCamera()->move(DOWN);
                break;
              case 32:
                //screenShot();
                break;
              case 341:
                //getCurrentCamera()->roll(-10.0f);
                break;
              case 340:
                //getCurrentCamera()->roll(10.0f);
                break;
              default:
                break;
            }
    }

    _sceneTree->animateScene();
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

const std::shared_ptr<ObjectNode>& Scene::getSceneTree() const
{
    return _sceneTree;
}

const std::shared_ptr<ObjectNode>& Scene::getCurrentNode() const
{
    return _currentNode;
}

void Scene::setCurrentNode(std::shared_ptr<ObjectNode> objectNode)
{
    _currentNode = objectNode;
}

const std::shared_ptr<Camera>& Scene::getCurrentCamera() const
{
    return _currentCamera;
}

const std::vector<std::shared_ptr<Camera>>& Scene::getCameras() const
{
    return _cameras;
}

void Scene::setCurrentCamera(std::shared_ptr<Camera> camera)
{
    _currentCamera = camera;
}

const std::vector<std::shared_ptr<Light>>& Scene::getLights() const
{
    return _lights;
}

const std::shared_ptr<RenderableObject>& Scene::getCurrentRenderableObject() const
{
    return _currentRenderableObject;
}

const std::vector<std::shared_ptr<RenderableObject>>& Scene::getRenderableObjects() const
{
    return _renderableObjects;
}

void Scene::setCurrentRenderableObject(std::shared_ptr<RenderableObject> renderableObject)
{
    _currentRenderableObject = renderableObject;
}
