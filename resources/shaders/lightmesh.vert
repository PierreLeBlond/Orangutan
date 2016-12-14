#version 450 core

in vec3 vertex_in;
in vec3 direction_in;
in int type_in;

out vec3 direction_out;
out int type_out;

void main(void)
{
    gl_Position = vec4(vertex_in, 1.0);
    direction_out = direction_in;
    type_out = type_in;
}

