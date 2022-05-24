#version 450 core

in vec2 uv_out;

uniform samplerCube source_map;

uniform float tile_width;
uniform float tile_height;
uniform float top;
uniform float left;

out vec4 color_out;

void main() {
  vec2 uv = uv_out*0.5 + 0.5;

  vec2 offseted_uv = uv - vec2(left, top);

  vec3 cube_uv = vec3(0.0);

  vec2 tiled_uv = offseted_uv/vec2(tile_width, tile_height);

  if (offseted_uv.y > 0.0 && offseted_uv.y < tile_height) {
    if (offseted_uv.x > tile_width && offseted_uv.x < 2.0*tile_width) {
      vec2 tiled_corrected_uv = (tiled_uv - vec2(1.0, 0.0)) * 2.0 - 1.0;
      cube_uv = vec3(tiled_corrected_uv.x, -1.0, tiled_corrected_uv.y);
    }
  } else if (offseted_uv.y > tile_height && offseted_uv.y < 2.0*tile_height) {
    if (offseted_uv.x > 0.0 && offseted_uv.x < tile_width) {
      vec2 tiled_corrected_uv = (tiled_uv - vec2(0.0, 1.0)) * 2.0 - 1.0;
      cube_uv = vec3(-1.0, tiled_corrected_uv.y, tiled_corrected_uv.x);
    } else if (offseted_uv.x > tile_width && offseted_uv.x < 2.0*tile_width) {
      vec2 tiled_corrected_uv = (tiled_uv - vec2(1.0, 1.0)) * 2.0 - 1.0;
      cube_uv = vec3(tiled_corrected_uv.x, tiled_corrected_uv.y, 1.0);
    } else if (offseted_uv.x > 2.0*tile_width && offseted_uv.x < 3.0*tile_width) {
      vec2 tiled_corrected_uv = (tiled_uv - vec2(2.0, 1.0)) * 2.0 - 1.0;
      cube_uv = vec3(1.0, tiled_corrected_uv.y, -tiled_corrected_uv.x);
    } else if (offseted_uv.x > 3.0*tile_width && offseted_uv.x < 4.0*tile_width) {
      vec2 tiled_corrected_uv = (tiled_uv - vec2(3.0, 1.0)) * 2.0 - 1.0;
      cube_uv = vec3(-tiled_corrected_uv.x, tiled_corrected_uv.y, -1.0);
    }
  } else if (offseted_uv.y > 2.0*tile_height && offseted_uv.y < 3.0*tile_height) {
    if (offseted_uv.x > tile_width && offseted_uv.x < 2.0*tile_width) {
      vec2 tiled_corrected_uv = (tiled_uv - vec2(1.0, 2.0)) * 2.0 - 1.0;
      cube_uv = vec3(tiled_corrected_uv.x, 1.0, -tiled_corrected_uv.y);
    }
  }

  cube_uv.xy = cube_uv.xy*2.0 - 1.0;

  color_out = textureLod(source_map, cube_uv, 0.0);
}
