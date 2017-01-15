#include "scene/scene.h"
#include "core/debug.h"
#include "util/keyboard.h"

Scene::Scene(std::shared_ptr<AssetsStorage> assetsStorage, int width, int height) :
    _assetsStorage(assetsStorage), _width(width), _height(height)
{
    auto universe = std::make_shared<Object>();
    auto universeNode = std::make_shared<ObjectNode>();
    universeNode->setObject(universe);

    _sceneTree = universeNode;

    //Cameras
    _currentCamera = std::make_shared<Camera>(_width, _height);

    _sceneTree->addChild(_currentCamera);

    //
    //CubeMap
    std::shared_ptr<RenderableObject> cubeMap = std::make_shared<RenderableObject>();
    cubeMap->setMesh(_assetsStorage->getMesh(1));
    cubeMap->setCubeMapId(_assetsStorage->getCubeMapTexture(1)->getId());
    cubeMap->setShaderStrategy(_assetsStorage->getShaderStrategy(1));
    cubeMap->fillInVBO();
    cubeMap->createVertexArrayObject();

    cubeMap->setXScale(10);
    cubeMap->setYScale(10);
    cubeMap->setZScale(10);

    _skyBox = cubeMap;

    auto cubeMapNode = std::make_shared<ObjectNode>();
    cubeMapNode->setObject(cubeMap);

    _currentCamera->addChild(cubeMapNode);

    std::shared_ptr<RenderableObject> object = std::make_shared<RenderableObject>();
    _currentRenderableObject = object;
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
    light->setYTranslationBigAxe(5);
    light->setYTranslationSmallAxe(5);
    light->setYTranslationSpeed(0.2);

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

void Scene::animate() {
    const std::vector<State>& keyboard = Keyboard::instance().getKeyboard();

    for(int key = 0; key < keyboard.size(); ++key)
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
                getCurrentCamera()->roll(-10.0f);
                break;
              case 340:
                getCurrentCamera()->roll(10.0f);
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

std::shared_ptr<Camera> Scene::getCurrentCamera(){
    return _currentCamera;
}

std::shared_ptr<RenderableObject> Scene::getCurrentRenderableObject(){
    return _currentRenderableObject;
}
