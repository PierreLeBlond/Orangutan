#version 450 core

in vec2 uv_out;

uniform sampler2D source_map;

out vec4 color_out;

void main() {
  color_out = texture(source_map, uv_out*0.5 + 0.5);
}
