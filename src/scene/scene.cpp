#include "scene/scene.h"

#include "core/debug.h"
#include "util/keyboard.h"

#include "camera/trackballcamera.h"
#include "camera/freecamera.h"

#include "model/objectsfactory.h"
#include "object/materialfactory.h"

Scene::Scene(const std::string& name) : Asset(name)
{
}

void Scene::build(Universe& universe)
{
    auto sceneNode = std::make_shared<ObjectNode>();

    addObjectNode(sceneNode);

    _sceneTree = sceneNode;

    //Cameras
    std::shared_ptr<TrackBallCamera> trackBallCamera = std::make_shared<TrackBallCamera>(600, 600);
    addCamera(trackBallCamera);
    setCurrentCamera(trackBallCamera);

    _sceneTree->addChild(trackBallCamera);

    std::shared_ptr<FreeCamera> freeCamera = std::make_shared<FreeCamera>(600, 600);
    addCamera(freeCamera);

    _sceneTree->addChild(trackBallCamera);

    //CubeMap
    std::shared_ptr<RenderableObject> cubeMap =
        ObjectsFactory::createRenderableObject(universe,
                                               "skybox",
                                               MaterialFactory::createSkyboxMaterial(),
                                               1,
                                               1,
                                               -1,
                                               1);
                                                                                       ;
    cubeMap->fillInVBO();
    cubeMap->initVertexArrayObject();

    cubeMap->setXScale(10);
    cubeMap->setYScale(10);
    cubeMap->setZScale(10);

    addRenderableObject(cubeMap);

    auto cubeMapNode = std::make_shared<ObjectNode>();
    cubeMapNode->setObject(cubeMap);

    addObjectNode(cubeMapNode);

    trackBallCamera->addChild(cubeMapNode);

    //mozart
    std::shared_ptr<RenderableObject> mozart =
        ObjectsFactory::createRenderableObject(universe,
                                               "Mozart",
                                               MaterialFactory::createDefaultMaterial(),
                                               3,
                                               0,
                                               2,
                                               1);
    mozart->fillInVBO();
    mozart->initVertexArrayObject();

    addRenderableObject(mozart);

    auto node = std::make_shared<ObjectNode>();
    node->setObject(mozart);
    node->setXPos(5);

    addObjectNode(node);

    _sceneTree->addChild(node);

    //Minion
    std::shared_ptr<RenderableObject> minion =
        ObjectsFactory::createRenderableObject(universe,
                                               "Minion",
                                               MaterialFactory::createDefaultMaterial(),
                                               2,
                                               0,
                                               1,
                                               1);
    minion->fillInVBO();
    minion->initVertexArrayObject();

    addRenderableObject(minion);

    setCurrentRenderableObject(minion);
    trackBallCamera->setFocusObject(getRenderableObjectLibrary().getCurrentItem());

    node = std::make_shared<ObjectNode>();
    node->setObject(minion);

    node->setXPos(-5);

    addObjectNode(node);

    _sceneTree->addChild(node);

    //Lights
    auto light = std::make_shared<Light>();
    light->setYTranslationBigAxe(5);
    light->setYTranslationSmallAxe(5);
    light->setYTranslationSpeed(0.2);

    addLight(light);

    auto lightNode = std::make_shared<ObjectNode>();
    lightNode->setObject(light);

    addObjectNode(lightNode);

    _sceneTree->addChild(lightNode);

    setIsReady(true);
}

void Scene::update()
{
    getCameraLibrary().getCurrentItem()->update();
    glm::mat4 mat(1.0);
    _sceneTree->updateScene(mat);
}

void Scene::animate() {
    const std::vector<State>& keyboard = Keyboard::instance().getKeyboard();

    for(unsigned int key = 0; key < keyboard.size(); ++key)
    {
        if(keyboard[key] == KEYNDOWN || keyboard[key] == KEYDOWN)
        {
            switch(key)
            {
              case 265:
                getCameraLibrary().getCurrentItem()->pitch(5.0f);
                break;
              case 264:
                getCameraLibrary().getCurrentItem()->pitch(-5.0f);
                break;
              case 262:
                getCameraLibrary().getCurrentItem()->yaw(5.0f);
                break;
              case 263:
                getCameraLibrary().getCurrentItem()->yaw(-5.0f);
                break;
              case 87:
                getCameraLibrary().getCurrentItem()->move(FORWARD);
                break;
              case 83:
                getCameraLibrary().getCurrentItem()->move(BACKWARD);
                break;
              case 65:
                getCameraLibrary().getCurrentItem()->move(LEFT);
                break;
              case 68:
                getCameraLibrary().getCurrentItem()->move(RIGHT);
                break;
              case 79:
                getCameraLibrary().getCurrentItem()->setOrthoProjectionMode();
                break;
              case 80:
                getCameraLibrary().getCurrentItem()->setPerspectiveProjectionMode();
                break;
              case 56:
                getRenderableObjectLibrary().getCurrentItem()->move(FORWARD);
                break;
              case 50:
                getRenderableObjectLibrary().getCurrentItem()->move(BACKWARD);
                break;
              case 52:
                getRenderableObjectLibrary().getCurrentItem()->move(LEFT);
                break;
              case 54:
                getRenderableObjectLibrary().getCurrentItem()->move(RIGHT);
                break;
              case 57:
                getRenderableObjectLibrary().getCurrentItem()->move(UP);
                break;
              case 51:
                getRenderableObjectLibrary().getCurrentItem()->move(DOWN);
                break;
              case 334:
                getCameraLibrary().getCurrentItem()->move(UP);
                break;
              case 333:
                getCameraLibrary().getCurrentItem()->move(DOWN);
                break;
              case 32:
                //screenShot();
                break;
              case 341:
                //getCameraLibrary().getCurrentItem()->roll(-10.0f);
                break;
              case 340:
                //getCameraLibrary().getCurrentItem()->roll(10.0f);
                break;
              default:
                break;
            }
        }
    }

    _sceneTree->animateScene();
}

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

