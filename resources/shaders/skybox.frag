#version 450 core

in vec3 uv_out;

uniform vec3 La;

uniform samplerCube cubeMap;

out vec4 color;

void main(void)
{
    color = texture(cubeMap, uv_out)*vec4(La, 1.0);
}

