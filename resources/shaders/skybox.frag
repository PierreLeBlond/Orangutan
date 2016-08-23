#version 330

in vec3 uv_out;

uniform vec3 La;

uniform samplerCube diffuseMap;

out vec4 color;

void main(void)
{
    color = texture(diffuseMap, uv_out)*vec4(La, 1.0);
}

