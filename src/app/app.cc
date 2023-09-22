#include "app/app.h"

#include <nanogui/layout.h>

#include <memory>
#include <string>
#include <vector>

#include "GLFW/glfw3.h"
#include "camera/freecamera.h"
#include "camera/trackballcamera.h"
#include "material/materialfactory.h"
#include "material/shaderfactory.h"
#include "mesh/meshfactory.h"
#include "nanogui/formhelper.h"
#include "nanogui/vector.h"
#include "object/renderableobject.h"
#include "object/renderableobjectfactory.h"
#include "scene/scenefactory.h"
#include "texture/texturefactory.h"
#include "ui/screen.h"

namespace orangutan {

void App::Init(GLFWwindow *window) {
  InitUniverse();

  // nanogui will take ownership via its own reference counter
  auto *screen = new Screen(window);

  // Init Screen presenter
  screen_presenter_ =
      std::make_unique<ScreenPresenter>(screen, universe_.get());

  BindEvents(window, screen);

  // Init Canvas

  // nanogui will take ownership via its own reference counter
  auto *canvas = new Canvas(screen);

  canvas_manager_ = std::make_unique<CanvasManager>(
      canvas, universe_->get_camera_library().GetItemByName("free_camera"),
      scene_.get());
  screen_presenter_->ConnectToResizeSignal(
      [&](unsigned int width, unsigned int height) {
        canvas_manager_->Resize(width, height);
      });

  texture_manager_ =
      std::make_unique<TextureManager>(universe_.get(), canvas, scene_.get());

  // nanogui will take ownership via its own reference counter
  texture_window_ =
      new TextureWindow(screen, "texture", texture_manager_.get());
  texture_window_->set_top(20);
  texture_window_->set_right(20);
  screen_presenter_->ConnectToResizeSignal(
      [&](unsigned int width, unsigned int height) {
        texture_window_->Resize(width, height);
      });

  // Init Universe presenter
  // nanogui will take ownership via its own reference counter
  // auto *universe_view = new Window(screen, "Universe");
  // universe_view->set_top(20);
  // universe_view->set_left(20);

  // universe_presenter_ = std::make_shared<UniversePresenter>(
  // universe_, screen_presenter_->get_context(), universe_view);
  // screen_presenter_->AddChildPresenter(universe_presenter_);

  // universe_presenter_->Init();

  screen_presenter_->Init();
}

void App::Draw() { screen_presenter_->Draw(); }

void App::BindEvents(GLFWwindow *window, Screen *screen) {
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
  universe_ = std::make_unique<Universe>();

  scene_ = std::make_unique<Scene>("scene");
  auto &scene_tree = scene_->get_scene_tree();

  const std::vector<std::string> no_defines;
  const std::vector<std::string> albedo_texture_defines{"ALBEDO_TEXTURE"};

  auto skybox_shader_wrapper = ShaderFactory::CreateShaderWrapper(
      "skybox_wrapper", no_defines, "../resources/shaders/skybox.vert",
      "../resources/shaders/skybox.frag");
  universe_->AddShaderWrapper(std::move(skybox_shader_wrapper));

  auto pbr_shader_wrapper = ShaderFactory::CreateShaderWrapper(
      "pbr", no_defines, "../resources/shaders/pbr.vert",
      "../resources/shaders/pbr.frag");
  universe_->AddShaderWrapper(std::move(pbr_shader_wrapper));

  auto brdf = TextureFactory::CreateBrdfMap();
  universe_->AddTexture(std::move(brdf));

  auto room_ibl = TextureFactory::ImportIBLFromDds(
      "room", "../resources/images/ibl/room/room_irradiance.dds",
      "../resources/images/ibl/room/room_radiance.dds");
  universe_->AddIbl(std::move(room_ibl));

  Assimp::Importer importer;

  universe_->AddMesh(MeshFactory::CreateCube("cube_mesh"));

  // Chess
  auto chess_node = universe_->AddObjectNode(SceneFactory::ImportSceneTree(
      importer, *universe_, "chess", "../resources/meshes/chess.gltf"));
  scene_tree.AddChild(chess_node);

  // Spheres
  // auto sphere_node = universe_->AddObjectNode(SceneFactory::ImportSceneTree(
  // importer, *universe_, "sphere", "../resources/meshes/spheres.gltf"));
  // scene_tree.AddChild(sphere_node);

  auto sky_material = MaterialFactory::CreateSkyboxMaterial();
  sky_material->set_shader_wrapper(
      universe_->get_shader_wrapper_library().GetItemByName("skybox_wrapper"));
  universe_->AddMaterial(std::move(sky_material));

  // Cameras
  auto freeCamera = std::make_unique<FreeCamera>("free_camera");
  freeCamera->set_speed(10.0f);
  freeCamera->set_position(glm::vec3(0.0f, 0.0f, 20.0f));
  universe_->AddCamera(std::move(freeCamera));

  // Sky
  auto sky = RenderableObjectFactory::CreateRenderableObject(
      *universe_, "skybox_renderable_object", "cube_mesh", "skybox_material");

  auto sky_node = std::make_unique<ObjectNode>("skybox_node");
  sky_node->set_object(sky.get());

  universe_->AddRenderableObject(std::move(sky));
  universe_->AddObjectNode(std::move(sky_node));

  // Lights
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      const std::string light_name =
          "light_" + std::to_string(i) + "_" + std::to_string(j);
      auto light = std::make_unique<Light>(light_name);

      light->set_intensity(1.0f);

      auto light_node = std::make_unique<ObjectNode>(light_name + "_node");
      light_node->set_object(light.get());
      light_node->set_position(
          glm::vec3(5.0f * (i * 2.0f - 1.0f), 5.0f * (j * 2.0f - 1.0f), 5.0f));

      scene_tree.AddChild(light_node.get());
      universe_->AddLight(std::move(light));
      universe_->AddObjectNode(std::move(light_node));
    }
  }

  // Cameras
  scene_tree.AddChild(
      universe_->get_camera_library().GetItemByName("free_camera"));

  // Sky
  scene_tree.AddChild(
      universe_->get_object_node_library().GetItemByName("skybox_node"));

  scene_->set_is_ready(true);

  scene_->SetIbl(universe_->get_ibl_library().GetItemByName("room"));
  scene_->SetBrdf(universe_->get_texture_library().GetItemByName("brdf"));
}

}  // namespace orangutan
