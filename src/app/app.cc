#include "app/app.h"

#include <nanogui/layout.h>

#include <memory>
#include <string>

#include "GLFW/glfw3.h"
#include "camera/freecamera.h"
#include "camera/trackballcamera.h"
#include "material/materialfactory.h"
#include "mesh/meshfactory.h"
#include "model/assetsfactory.h"
#include "nanogui/formhelper.h"
#include "nanogui/vector.h"
#include "object/renderableobject.h"
#include "object/renderableobjectfactory.h"
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

  auto skybox_shader_wrapper = AssetsFactory::CreateShaderWrapper(
      "skybox", "../resources/shaders/skybox.vert",
      "../resources/shaders/skybox.frag");
  auto skybox_shader_strategy = AssetsFactory::CreateShaderStrategy(
      skybox_shader_wrapper.get(), "Skybox");
  universe_->AddShaderWrapper(std::move(skybox_shader_wrapper));
  universe_->AddShaderStrategy(std::move(skybox_shader_strategy));

  auto pbr_shader_wrapper = AssetsFactory::CreateShaderWrapper(
      "pbr", "../resources/shaders/pbr.vert", "../resources/shaders/pbr.frag");
  auto pbr_shader_strategy =
      AssetsFactory::CreateShaderStrategy(pbr_shader_wrapper.get(), "pbr");
  universe_->AddShaderWrapper(std::move(pbr_shader_wrapper));
  universe_->AddShaderStrategy(std::move(pbr_shader_strategy));

  auto brdf = TextureFactory::CreateBrdfMap();
  universe_->AddTexture(std::move(brdf));

  auto subway_ibl = TextureFactory::ImportIBLFromDds(
      "subway", "../resources/images/ibl/subway/subway_irradiance.dds",
      "../resources/images/ibl/subway/subway_radiance.dds");
  universe_->AddIbl(std::move(subway_ibl));

  auto bridge_ibl = TextureFactory::ImportIBLFromDds(
      "bridge", "../resources/images/ibl/bridge/bridge_irradiance.dds",
      "../resources/images/ibl/bridge/bridge_radiance.dds");
  universe_->AddIbl(std::move(bridge_ibl));

  auto studio_ibl = TextureFactory::ImportIBLFromDds(
      "studio", "../resources/images/ibl/studio_3/studio_3_irradiance.dds",
      "../resources/images/ibl/studio_3/studio_3_radiance.dds");
  universe_->AddIbl(std::move(studio_ibl));

  universe_->AddMesh(MeshFactory::CreateCube("Cube"));
  universe_->AddMesh(std::move(
      AssetsFactory::ImportMeshs("../resources/meshes/sphere.obj")[0]));

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 2; j++) {
      const std::string material_name =
          "pbr_material_" + std::to_string(i) + "_" + std::to_string(j);
      auto material = MaterialFactory::CreatePbrMaterial(material_name);
      material->SetUniform("albedo", glm::vec3(1.0f, 1.0f, 1.0f));
      material->SetUniform("roughness", float(i) * 0.1f);
      material->SetUniform("metalness", float(j) * 1.0f);

      universe_->AddMaterial(std::move(material));

      const std::string renderable_object_name =
          "sphere_" + std::to_string(i) + "_" + std::to_string(j);

      auto sphere = RenderableObjectFactory::CreateRenderableObject(
          *universe_, renderable_object_name, "sphere", material_name, "pbr");
      sphere->UpdateVertexArrayObject();

      auto sphere_node =
          std::make_unique<ObjectNode>(renderable_object_name + "_node");
      sphere_node->set_object(sphere.get());

      sphere_node->SetXPos((float)i * 3.0f - 13.5f);
      sphere_node->SetYPos((float)j * 3.0f);

      universe_->AddRenderableObject(std::move(sphere));
      universe_->AddObjectNode(std::move(sphere_node));
    }
  }

  auto sky_material = MaterialFactory::CreateSkyboxMaterial();
  universe_->AddMaterial(std::move(sky_material));

  // Cameras
  auto freeCamera = std::make_unique<FreeCamera>("free_camera");
  freeCamera->set_speed(10.0f);
  freeCamera->set_position(glm::vec3(0.0f, 0.0f, 20.0f));
  universe_->AddCamera(std::move(freeCamera));

  // Sky
  auto sky = RenderableObjectFactory::CreateRenderableObject(
      *universe_, "sky", "Cube", "Skybox", "Skybox");
  sky->UpdateVertexArrayObject();

  auto sky_node = std::make_unique<ObjectNode>("sky_node");
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

      auto lightNode = std::make_unique<ObjectNode>(light_name + "_node");
      lightNode->set_object(light.get());
      lightNode->set_position(
          glm::vec3(5.0f * (i * 2.0f - 1.0f), 5.0f * (j * 2.0f - 1.0f), 5.0f));

      universe_->AddLight(std::move(light));
      universe_->AddObjectNode(std::move(lightNode));
    }
  }

  scene_ = std::make_unique<Scene>("scene");
  scene_->Build(*universe_);

  scene_->SetIbl(universe_->get_ibl_library().GetItemByName("studio"));
  scene_->SetBrdf(universe_->get_texture_library().GetItemByName("brdf"));
}

}  // namespace orangutan
