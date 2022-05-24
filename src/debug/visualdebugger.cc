#include "debug/visualdebugger.h"

#include "mesh/meshfactory.h"

namespace orangutan {

void VisualDebugger::DisplayTexture(const Texture& texture) {
  if (!texture_displayer_) {
    // shader wrapper
    texture_displayer_shader_wrapper_ =
        std::make_unique<ShaderWrapper>("texture_debug_shader_wrapper");

    texture_displayer_shader_wrapper_->build(
        "../resources/shaders/texture_debug.vert",
        "../resources/shaders/texture_debug.frag", "");

    // shader strategy
    texture_displayer_shader_strategy_ =
        std::make_unique<ShaderStrategy>("texture_debug_shader_strategy");

    texture_displayer_shader_strategy_->set_shader_wrapper(
        texture_displayer_shader_wrapper_.get());
    texture_displayer_shader_strategy_->InitAttribute();

    // mesh
    texture_displayer_mesh_ =
        orangutan::MeshFactory::CreateSquare("texture_debug_square");

    // renderable object
    texture_displayer_ =
        std::make_unique<RenderableObject>("texture_debug_renderable_object");
    texture_displayer_->set_shader_strategy(
        texture_displayer_shader_strategy_.get());
    texture_displayer_->set_mesh(texture_displayer_mesh_.get());
    texture_displayer_->UpdateVertexArrayObject();
  }

  texture_displayer_->get_shader_strategy().get_shader_wrapper().bindTexture(
      "source_map", texture.getId());
  texture_displayer_->Draw();
}

void VisualDebugger::DisplayCubeTexture(const CubeTexture& cube_texture,
                                        int width, int height) {
  if (!cube_texture_displayer_) {
    // shader wrapper
    cube_texture_displayer_shader_wrapper_ =
        std::make_unique<ShaderWrapper>("cube_texture_debug_shader_wrapper");

    cube_texture_displayer_shader_wrapper_->build(
        "../resources/shaders/cube_texture_debug.vert",
        "../resources/shaders/cube_texture_debug.frag", "");

    // shader strategy
    cube_texture_displayer_shader_strategy_ =
        std::make_unique<ShaderStrategy>("cube_texture_debug_shader_strategy");

    cube_texture_displayer_shader_strategy_->set_shader_wrapper(
        cube_texture_displayer_shader_wrapper_.get());
    cube_texture_displayer_shader_strategy_->InitAttribute();

    // mesh
    cube_texture_displayer_mesh_ =
        orangutan::MeshFactory::CreateSquare("cube_texture_debug_square");

    // renderable object
    cube_texture_displayer_ = std::make_unique<RenderableObject>(
        "cube_texture_debug_renderable_object");
    cube_texture_displayer_->set_shader_strategy(
        cube_texture_displayer_shader_strategy_.get());
    cube_texture_displayer_->set_mesh(cube_texture_displayer_mesh_.get());
    cube_texture_displayer_->UpdateVertexArrayObject();
  }

  float tile_width = (float)width / 4.0f;
  float tile_height = (float)height / 3.0f;

  float tile_size = fmin(tile_width, tile_height);

  float top = ((float)height - 3.0f * tile_size) / 2.0f;
  float left = ((float)width - 4.0f * tile_size) / 2.0f;

  cube_texture_displayer_->get_shader_strategy().get_shader_wrapper().start();

  cube_texture_displayer_->get_shader_strategy()
      .get_shader_wrapper()
      .setUniform("tile_width", tile_size / (float)width);
  cube_texture_displayer_->get_shader_strategy()
      .get_shader_wrapper()
      .setUniform("tile_height", tile_size / (float)height);
  cube_texture_displayer_->get_shader_strategy()
      .get_shader_wrapper()
      .setUniform("top", top / (float)height);
  cube_texture_displayer_->get_shader_strategy()
      .get_shader_wrapper()
      .setUniform("left", left / (float)width);

  cube_texture_displayer_->get_shader_strategy()
      .get_shader_wrapper()
      .bindCubeTexture("source_map", cube_texture.getId());

  cube_texture_displayer_->get_shader_strategy().get_shader_wrapper().stop();

  cube_texture_displayer_->Draw();
}

}  // namespace orangutan
