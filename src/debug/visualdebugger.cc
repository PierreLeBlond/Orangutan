#include "debug/visualdebugger.h"

#include "mesh/meshfactory.h"

namespace orangutan {

void VisualDebugger::DisplayTexture(const Texture& texture) {
  if (!texture_displayer_) {
    // shader wrapper
    texture_displayer_shader_wrapper_ =
        std::make_unique<ShaderWrapper>("texture_debug_shader_wrapper");

    const std::vector<std::string> no_defines;
    texture_displayer_shader_wrapper_->Build(
        no_defines, "../resources/shaders/texture_debug.vert",
        "../resources/shaders/texture_debug.frag", "");

    // material
    texture_displayer_material_ =
        std::make_unique<Material>("texture_debug_material");

    texture_displayer_material_->set_shader_wrapper(
        texture_displayer_shader_wrapper_.get());

    // mesh
    texture_displayer_mesh_ =
        orangutan::MeshFactory::CreateSquare("texture_debug_square");

    // renderable object
    texture_displayer_ =
        std::make_unique<RenderableObject>("texture_debug_renderable_object");
    texture_displayer_->set_material(texture_displayer_material_.get());
    texture_displayer_->set_mesh(texture_displayer_mesh_.get());
    texture_displayer_->UpdateVertexArrayObject();
  }

  texture_displayer_->get_material().get_shader_wrapper().BindTexture(
      "source_map", texture.getId());
  texture_displayer_->Draw();
}

void VisualDebugger::DisplayCubeTexture(const CubeTexture& cube_texture,
                                        int width, int height) {
  if (!cube_texture_displayer_) {
    // shader wrapper
    cube_texture_displayer_shader_wrapper_ =
        std::make_unique<ShaderWrapper>("cube_texture_debug_shader_wrapper");

    const std::vector<std::string> no_defines;
    cube_texture_displayer_shader_wrapper_->Build(
        no_defines, "../resources/shaders/cube_texture_debug.vert",
        "../resources/shaders/cube_texture_debug.frag", "");

    // shader strategy
    cube_texture_displayer_material_ =
        std::make_unique<Material>("cube_texture_debug_shader_strategy");

    cube_texture_displayer_material_->set_shader_wrapper(
        cube_texture_displayer_shader_wrapper_.get());

    // mesh
    cube_texture_displayer_mesh_ =
        orangutan::MeshFactory::CreateSquare("cube_texture_debug_square");

    // renderable object
    cube_texture_displayer_ = std::make_unique<RenderableObject>(
        "cube_texture_debug_renderable_object");
    cube_texture_displayer_->set_material(
        cube_texture_displayer_material_.get());
    cube_texture_displayer_->set_mesh(cube_texture_displayer_mesh_.get());
    cube_texture_displayer_->UpdateVertexArrayObject();
  }

  float tile_width = (float)width / 4.0f;
  float tile_height = (float)height / 3.0f;

  float tile_size = fmin(tile_width, tile_height);

  float top = ((float)height - 3.0f * tile_size) / 2.0f;
  float left = ((float)width - 4.0f * tile_size) / 2.0f;

  cube_texture_displayer_->get_material().get_shader_wrapper().Start();

  cube_texture_displayer_->get_material().get_shader_wrapper().BindUniform(
      "tile_width", tile_size / (float)width);
  cube_texture_displayer_->get_material().get_shader_wrapper().BindUniform(
      "tile_height", tile_size / (float)height);
  cube_texture_displayer_->get_material().get_shader_wrapper().BindUniform(
      "top", top / (float)height);
  cube_texture_displayer_->get_material().get_shader_wrapper().BindUniform(
      "left", left / (float)width);

  cube_texture_displayer_->get_material().get_shader_wrapper().BindCubeTexture(
      "source_map", cube_texture.getId());

  cube_texture_displayer_->get_material().get_shader_wrapper().Stop();

  cube_texture_displayer_->Draw();
}

}  // namespace orangutan
