#include "app/app.h"

#include <memory>
#include <string>
#include <vector>

#include "camera/freecamera.h"
#include "core/debug.h"
#include "material/materialfactory.h"
#include "material/shaderfactory.h"
#include "mesh/meshfactory.h"
#include "object/renderableobjectfactory.h"
#include "scene/scenefactory.h"
#include "texture/texturefactory.h"

namespace orangutan {

TextureManager *App::get_texture_manager() const {
  return texture_manager_.get();
}

void App::Init() {
  universe_ = std::make_unique<Universe>();

  scene_ = std::make_unique<Scene>("scene");
  auto &scene_tree = scene_->get_scene_tree();

  const std::vector<std::string> no_defines;
  const std::vector<std::string> albedo_texture_defines{"ALBEDO_TEXTURE"};

  auto skybox_shader_wrapper = ShaderFactory::CreateShaderWrapper(
      "skybox_wrapper", no_defines, "./resources/shaders/skybox.vert",
      "./resources/shaders/skybox.frag");
  universe_->AddShaderWrapper(std::move(skybox_shader_wrapper));

  auto pbr_shader_wrapper = ShaderFactory::CreateShaderWrapper(
      "pbr", no_defines, "./resources/shaders/pbr.vert",
      "./resources/shaders/pbr.frag");
  universe_->AddShaderWrapper(std::move(pbr_shader_wrapper));

  auto brdf = TextureFactory::CreateBrdfMap();
  universe_->AddTexture(std::move(brdf));

  auto sky_ibl = TextureFactory::ImportIBLFromHdr(
      "sky", "./resources/images/ibl/rustig_koppie_puresky_1k.hdr");
  universe_->AddIbl(std::move(sky_ibl));

  auto studio_ibl = TextureFactory::ImportIBLFromHdr(
      "studio", "./resources/images/ibl/studio.hdr");
  universe_->AddIbl(std::move(studio_ibl));

  Assimp::Importer importer;

  // Spheres
  auto spheres_node = universe_->AddObjectNode(SceneFactory::ImportSceneTree(
      importer, *universe_, "sphere", "./resources/meshes/", "spheres.gltf"));
  scene_tree.AddChild(spheres_node);

  // Cameras
  camera_ = std::make_unique<FreeCamera>("free_camera");
  camera_->set_speed(10.0f);
  camera_->set_position(glm::vec3(0.0f, 0.0f, 20.0f));
  camera_controller_ = std::make_unique<CameraController>(camera_.get());

  scene_tree.AddChild(camera_.get());

  // Sky
  universe_->AddMesh(MeshFactory::CreateCube("cube_mesh"));

  auto sky_material = MaterialFactory::CreateSkyboxMaterial();
  sky_material->set_shader_wrapper(
      universe_->get_shader_wrapper_library().GetItemByName("skybox_wrapper"));
  universe_->AddMaterial(std::move(sky_material));

  auto sky = RenderableObjectFactory::CreateRenderableObject(
      *universe_, "skybox_renderable_object", "cube_mesh", "skybox_material");

  auto sky_node = std::make_unique<ObjectNode>("skybox_node");
  sky_node->set_object(sky.get());

  universe_->AddRenderableObject(std::move(sky));
  universe_->AddObjectNode(std::move(sky_node));
  scene_tree.AddChild(
      universe_->get_object_node_library().GetItemByName("skybox_node"));

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

  scene_->set_is_ready(true);

  scene_->SetIbl(universe_->get_ibl_library().GetItemByName("studio"));
  scene_->SetBrdf(universe_->get_texture_library().GetItemByName("brdf"));

  texture_manager_ =
      std::make_unique<TextureManager>(universe_.get(), scene_.get());
}

void App::Draw(int width, int height) {
  double current_time = glfwGetTime();
  double delta_time = current_time - last_update_time_;
  last_update_time_ = current_time;

  camera_controller_->SetSize(width, height);
  camera_controller_->Update(delta_time);
  camera_->Update();

  scene_->Animate();
  scene_->Update();

  GL_CHECK_ERROR(glEnable(GL_DEPTH_TEST));
  GL_CHECK_ERROR(glDisable(GL_BLEND));
  GL_CHECK_ERROR(glDisable(GL_CULL_FACE));
  // For sky box to render properly
  GL_CHECK_ERROR(glDepthFunc(GL_LEQUAL));

  scene_->Draw(camera_->get_view_matrix(),
               camera_->get_transform().get_position(),
               camera_->get_projection_matrix());
}

} // namespace orangutan
