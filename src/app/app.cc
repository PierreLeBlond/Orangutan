#include "app/app.h"

#include <nanogui/layout.h>

#include <memory>

#include "GLFW/glfw3.h"
#include "camera/freecamera.h"
#include "camera/trackballcamera.h"
#include "model/assetsfactory.h"
#include "model/objectsfactory.h"
#include "nanogui/formhelper.h"
#include "object/materialfactory.h"
#include "object/renderableobject.h"
#include "view/screen.h"

void App::Init(GLFWwindow *window) {
  InitUniverse();

  // nanogui will take ownership via its own reference counter
  auto *screen = new orangutan::Screen(window);

  screen->set_resize_callback(
      [&](nanogui::Vector2i size) { Resize(size.x(), size.y()); });

  // Init Screen presenter
  _screenPresenter = std::make_shared<ScreenPresenter>(screen, _universe);

  BindEvents(window, screen);

  // Init Canvas presenter

  // nanogui will take ownership via its own reference counter
  auto *canvas = new Canvas(screen);

  _canvasPresenter = std::make_shared<CanvasPresenter>(
      _universe, _screenPresenter->get_context(), canvas);
  _screenPresenter->AddChildPresenter(_canvasPresenter);

  // Init Universe presenter
  // nanogui will take ownership via its own reference counter
  auto *universe_view = new View(screen, "Universe");

  _universePresenter = std::make_shared<UniversePresenter>(
      _universe, _screenPresenter->get_context(), universe_view);
  _screenPresenter->AddChildPresenter(_universePresenter);

  // Init RenderableObject presenter
  // nanogui will take ownership via its own reference counter
  auto *renderable_object_view = new View(screen, "Renderable Object");

  _renderableObjectPresenter = std::make_shared<RenderableObjectPresenter>(
      _universe, _screenPresenter->get_context(), renderable_object_view);
  _screenPresenter->AddChildPresenter(_renderableObjectPresenter);

  _canvasPresenter->Init();
  _universePresenter->Init();
  _renderableObjectPresenter->Init();

  _screenPresenter->Init();
}

void App::Draw() { _screenPresenter->Draw(); }

void App::Resize(unsigned int width, unsigned int height) {
  _canvasPresenter->Resize(width, height);
  _universePresenter->Resize(width / 5, height);
  _renderableObjectPresenter->Resize(width / 5, height);
}

void App::BindEvents(GLFWwindow *window, orangutan::Screen *screen) {
  // Cheers to http://www.alecjacobson.com/weblog/?p=3779

  // cursor_pos_callback_event
  static std::function<void(GLFWwindow *, double x, double y)>
      cursor_pos_callback_bounce;
  auto cursor_pos_callback = [](GLFWwindow *window, double x, double y) {
    cursor_pos_callback_bounce(window, x, y);
  };
  cursor_pos_callback_bounce = [screen](GLFWwindow *, double x, double y) {
    screen->cursor_pos_callback_event(x, y);
  };

  glfwSetCursorPosCallback(window, cursor_pos_callback);

  // mouse_button_callback_event
  static std::function<void(GLFWwindow *, int button, int action,
                            int modifiers)>
      mouse_button_callback_bounce;
  auto mouse_button_callback = [](GLFWwindow *window, int button, int action,
                                  int modifiers) {
    mouse_button_callback_bounce(window, button, action, modifiers);
  };
  mouse_button_callback_bounce = [screen](GLFWwindow *, int button, int action,
                                          int modifiers) {
    screen->mouse_button_callback_event(button, action, modifiers);
  };

  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // key_callback_event
  static std::function<void(GLFWwindow *, int key, int scancode, int action,
                            int mods)>
      key_callback_bounce;
  auto key_callback = [](GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    key_callback_bounce(window, key, scancode, action, mods);
  };
  key_callback_bounce = [screen](GLFWwindow *, int key, int scancode,
                                 int action, int mods) {
    screen->key_callback_event(key, scancode, action, mods);
  };

  glfwSetKeyCallback(window, key_callback);

  // char_callback_event
  static std::function<void(GLFWwindow *, unsigned int codepoint)>
      char_callback_bounce;
  auto char_callback = [](GLFWwindow *window, unsigned int codepoint) {
    char_callback_bounce(window, codepoint);
  };
  char_callback_bounce = [screen](GLFWwindow *, unsigned int codepoint) {
    screen->char_callback_event(codepoint);
  };

  glfwSetCharCallback(window, char_callback);

  // drop_callback_event
  static std::function<void(GLFWwindow *, int count, const char **filenames)>
      drop_callback_bounce;
  auto drop_callback = [](GLFWwindow *window, int count,
                          const char **filenames) {
    drop_callback_bounce(window, count, filenames);
  };
  drop_callback_bounce = [screen](GLFWwindow *, int count,
                                  const char **filenames) {
    screen->drop_callback_event(count, filenames);
  };

  glfwSetDropCallback(window, drop_callback);

  // scroll_callback_event
  static std::function<void(GLFWwindow *, double x, double y)>
      scroll_callback_bounce;
  auto scroll_callback = [](GLFWwindow *window, double x, double y) {
    scroll_callback_bounce(window, x, y);
  };
  scroll_callback_bounce = [screen](GLFWwindow *, double x, double y) {
    screen->scroll_callback_event(x, y);
  };

  glfwSetScrollCallback(window, scroll_callback);

  // resize_callback_event
  static std::function<void(GLFWwindow *, int width, int height)>
      resize_callback_bounce;
  auto resize_callback = [](GLFWwindow *window, int width, int height) {
    resize_callback_bounce(window, width, height);
  };
  resize_callback_bounce = [screen](GLFWwindow *, int width, int height) {
    screen->resize_callback_event(width, height);
  };

  glfwSetFramebufferSizeCallback(window, resize_callback);
}

void App::InitUniverse() {
  _universe = std::make_shared<Universe>();

  // std::cout << "Shader phong" << std::endl;
  std::shared_ptr<ShaderWrapper> shaderWrapper;
  shaderWrapper = AssetsFactory::instance().importShader(
      "../resources/shaders/phong.vert", "../resources/shaders/phong.frag");
  _universe->AddShaderWrapper(shaderWrapper);
  _universe->AddShaderStrategy(
      AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Phong"));

  // std::cout << "Shader skybox" << std::endl;
  shaderWrapper = AssetsFactory::instance().importShader(
      "../resources/shaders/skybox.vert", "../resources/shaders/skybox.frag");
  _universe->AddShaderWrapper(shaderWrapper);
  _universe->AddShaderStrategy(
      AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Skybox"));

  // std::cout << "Shader environment" << std::endl;
  shaderWrapper = AssetsFactory::instance().importShader(
      "../resources/shaders/environmentmap.vert",
      "../resources/shaders/environmentmap.frag");
  _universe->AddShaderWrapper(shaderWrapper);
  _universe->AddShaderStrategy(AssetsFactory::instance().createShaderStrategy(
      shaderWrapper, "Environment"));

  // std::cout << "Shader gouraud" << std::endl;
  shaderWrapper = AssetsFactory::instance().importShader(
      "../resources/shaders/shader.vert", "../resources/shaders/shader.frag");
  _universe->AddShaderWrapper(shaderWrapper);
  _universe->AddShaderStrategy(
      AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Gouraud"));

  // std::cout << "Shader toon" << std::endl;
  shaderWrapper = AssetsFactory::instance().importShader(
      "../resources/shaders/toon.vert", "../resources/shaders/toon.frag");
  _universe->AddShaderWrapper(shaderWrapper);
  _universe->AddShaderStrategy(
      AssetsFactory::instance().createShaderStrategy(shaderWrapper, "Toon"));
  /*
     std::cout << "Shader edge" << std::endl;
     shaderWrapper =
     AssetsFactory::instance().importShader("../resources/shaders/edgefilter.vert",
     "../resources/shaders/edgefilter.frag");
     AssetsFactory::instance().createNewScreenSpaceShaderStrategy(EDGEFILTER, 5,
     "edgeFilter");

     std::cout << "Shader gaussian" << std::endl;
     shaderWrapper =
     AssetsFactory::instance().importShader("../resources/shaders/edgefilter.vert",
     "../resources/shaders/verticalgaussianblurfilter.frag");
     AssetsFactory::instance().createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER,
     6, "verticalGaussianBlur");

     std::cout << "Shader gaussian" << std::endl;
     shaderWrapper =
     AssetsFactory::instance().importShader("../resources/shaders/edgefilter.vert",
     "../resources/shaders/horizontalgaussianblurfilter.frag");
     AssetsFactory::instance().createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER,
     7, "horizontalGaussianBlur");
     */

  std::shared_ptr<DDTexture> texture2D;
  texture2D = AssetsFactory::instance().importTexture(
      "../resources/images/Texture/dice.png", "dice");
  _universe->AddTexture(texture2D);
  texture2D = AssetsFactory::instance().importTexture(
      "../resources/images/Texture/Minion.png", "minion");
  _universe->AddTexture(texture2D);
  texture2D = AssetsFactory::instance().importTexture(
      "../resources/images/Texture/Mozart.png", "mozart");
  _universe->AddTexture(texture2D);

  std::shared_ptr<CubeTexture> textureCube;
  textureCube = AssetsFactory::instance().importCubeMapTexture(
      "../resources/images/Skybox/space_", "space");
  _universe->AddCubeTexture(textureCube);
  textureCube = AssetsFactory::instance().importCubeMapTexture(
      "../resources/images/Skybox/sky_", "sky");
  _universe->AddCubeTexture(textureCube);

  _universe->AddMesh(Mesh::createSquare("Square"));
  _universe->AddMesh(Mesh::createCube(1, "Cube"));
  //_universe->addMesh(Mesh::createSphere(8, "Sphere"));
  //_universe->addMesh(Mesh::createCylinder(8, "Cylinder"));

  std::shared_ptr<Mesh> mesh;
  mesh = AssetsFactory::instance().importMeshs(
      "../resources/meshes/minion.obj")[0];
  _universe->AddMesh(mesh);
  mesh = AssetsFactory::instance().importMeshs(
      "../resources/meshes/mozart.obj")[0];
  _universe->AddMesh(mesh);
  mesh =
      AssetsFactory::instance().importMeshs("../resources/meshes/axes.obj")[0];
  _universe->AddMesh(mesh);

  // Cameras
  std::shared_ptr<TrackBallCamera> trackBallCamera =
      std::make_shared<TrackBallCamera>("track_ball_camera");
  _universe->AddCamera(trackBallCamera);

  std::shared_ptr<FreeCamera> freeCamera =
      std::make_shared<FreeCamera>("free_camera");
  freeCamera->set_speed(5.0f);
  freeCamera->set_position(glm::vec3(0.0f, 0.0f, 10.0f));
  _universe->AddCamera(freeCamera);
  _universe->SetCurrentCamera(freeCamera);

  std::shared_ptr<RenderableObject> cubeMap =
      ObjectsFactory::createRenderableObject(
          *_universe, "skybox", MaterialFactory::createSkyboxMaterial(), 1, 1,
          -1, 1);
  ;
  cubeMap->fillInVBO();
  cubeMap->initVertexArrayObject();

  cubeMap->SetXScale(50);
  cubeMap->SetYScale(50);
  cubeMap->SetZScale(50);

  _universe->AddRenderableObject(cubeMap);

  auto cubeMapNode = std::make_shared<ObjectNode>("cube_map");
  cubeMapNode->set_object(cubeMap);

  _universe->AddObjectNode(cubeMapNode);

  trackBallCamera->AddChild(cubeMapNode);

  // Axes

  std::shared_ptr<RenderableObject> axes =
      ObjectsFactory::createRenderableObject(
          *_universe, "Axes", MaterialFactory::createDefaultMaterial(), 4, 0, 1,
          1);
  axes->fillInVBO();
  axes->initVertexArrayObject();

  _universe->AddRenderableObject(axes);

  auto axes_node = std::make_shared<ObjectNode>("axes_node");
  axes_node->set_object(axes);

  _universe->AddObjectNode(axes_node);

  _universe->SetCurrentRenderableObject(axes);

  // Lights
  auto light = std::make_shared<Light>();

  _universe->AddLight(light);

  auto lightNode = std::make_shared<ObjectNode>("light_node");
  lightNode->set_object(light);

  _universe->AddObjectNode(lightNode);

  _scene = std::make_shared<Scene>("scene");
  _scene->Build(*_universe);

  _universe->AddScene(_scene);
  _universe->SetCurrentScene(_scene);

  _universe->AddObjectNode(_scene->get_scene_tree());
}

