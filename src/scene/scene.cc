#include "scene/scene.h"

#include <memory>

#include "camera/freecamera.h"
#include "camera/trackballcamera.h"
#include "core/debug.h"
#include "model/universe.h"
#include "util/keyboard.h"

Scene::Scene(const std::string& name)
    : Asset(name),
      scene_tree_(std::make_shared<ObjectNode>("scene_node")),
      is_ready_(false) {}

void Scene::Build(const Universe& universe) {
  auto sceneNode = std::make_shared<ObjectNode>("scene_node");

  // Cameras
  scene_tree_->AddChild(
      universe.get_camera_library().GetItemsByName("track_ball_camera")[0]);

  scene_tree_->AddChild(
      universe.get_camera_library().GetItemsByName("free_camera")[0]);

  // CubeMap
  // mozart
  // std::shared_ptr<RenderableObject> mozart =
  // ObjectsFactory::createRenderableObject(
  // universe, "Mozart", MaterialFactory::createDefaultMaterial(), 3, 0, 2,
  // 1);
  // mozart->fillInVBO();
  // mozart->initVertexArrayObject();

  // addRenderableObject(mozart);

  // auto node = std::make_shared<ObjectNode>("node");
  // node->set_object(mozart);

  // addObjectNode(node);

  // scene_tree_->AddChild(node);

  // Minion
  // std::shared_ptr<RenderableObject> minion =
  // ObjectsFactory::createRenderableObject(
  // universe, "Minion", MaterialFactory::createDefaultMaterial(), 2, 0, 1,
  // 1);
  // minion->fillInVBO();
  // minion->initVertexArrayObject();

  // addRenderableObject(minion);

  // setCurrentRenderableObject(minion);
  // trackBallCamera->set_focus_object(
  // getRenderableObjectLibrary().getCurrentItem());

  // node = std::make_shared<ObjectNode>("minion_node");
  // node->set_object(minion);

  // addObjectNode(node);

  // scene_tree_->AddChild(node);

  // Axes
  scene_tree_->AddChild(
      universe.get_object_node_library().GetItemsByName("axes_node")[0]);

  // Lights
  scene_tree_->AddChild(
      universe.get_object_node_library().GetItemsByName("light_node")[0]);

  set_is_ready(true);
}

void Scene::Update() {
  glm::mat4 mat(1.0);
  scene_tree_->UpdateScene(mat);
}

void Scene::Animate() {
  const std::vector<KeyState>& keyboard = Keyboard::instance().getKeyboard();

  // for (auto key : keyboard) {
  // if (key == KEYNDOWN || key == KEYDOWN) {
  // switch (key) {
  // case 265:
  // getCameraLibrary().getCurrentItem()->Pitch(5.0f);
  // break;
  // case 264:
  // getCameraLibrary().getCurrentItem()->Pitch(-5.0f);
  // break;
  // case 262:
  // getCameraLibrary().getCurrentItem()->Yaw(5.0f);
  // break;
  // case 263:
  // getCameraLibrary().getCurrentItem()->Yaw(-5.0f);
  // break;
  // case 87:
  // getCameraLibrary().getCurrentItem()->Move(FORWARD);
  // break;
  // case 83:
  // getCameraLibrary().getCurrentItem()->Move(BACKWARD);
  // break;
  // case 65:
  // getCameraLibrary().getCurrentItem()->move(LEFT);
  // break;
  // case 68:
  // getCameraLibrary().getCurrentItem()->move(RIGHT);
  // break;
  // case 79:
  // getCameraLibrary().getCurrentItem()->setOrthoProjectionMode();
  // break;
  // case 80:
  // getCameraLibrary().getCurrentItem()->setPerspectiveProjectionMode();
  // break;
  // case 56:
  // getRenderableObjectLibrary().getCurrentItem()->move(FORWARD);
  // break;
  // case 50:
  // getRenderableObjectLibrary().getCurrentItem()->move(BACKWARD);
  // break;
  // case 52:
  // getRenderableObjectLibrary().getCurrentItem()->move(LEFT);
  // break;
  // case 54:
  // getRenderableObjectLibrary().getCurrentItem()->move(RIGHT);
  // break;
  // case 57:
  // getRenderableObjectLibrary().getCurrentItem()->move(UP);
  // break;
  // case 51:
  // getRenderableObjectLibrary().getCurrentItem()->move(DOWN);
  // break;
  // case 334:
  // getCameraLibrary().getCurrentItem()->move(UP);
  // break;
  // case 333:
  // getCameraLibrary().getCurrentItem()->move(DOWN);
  // break;
  // case 32:
  // // screenShot();
  // break;
  // case 341:
  // // getCameraLibrary().getCurrentItem()->roll(-10.0f);
  // break;
  // case 340:
  // // getCameraLibrary().getCurrentItem()->roll(10.0f);
  // break;
  // default:
  // break;
  // }
  // }
  // }

  scene_tree_->AnimateScene();
}

void Scene::set_is_ready(bool isReady) { is_ready_ = isReady; }

bool Scene::get_is_ready() const { return is_ready_; }

const std::shared_ptr<ObjectNode>& Scene::get_scene_tree() const {
  return scene_tree_;
}

