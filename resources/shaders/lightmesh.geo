layout(points) in;
layout(line_strip, max_vertices = 224) out;

uniform mat4 projection;
uniform mat4 view;

in vec3 direction_out[];
in int type_out[];

void main()
{
    for(int i = 0; i < direction_out.length();i++){
    vec4 front = normalize(vec4(direction_out[i], 1.0));
    vec4 up = normalize(vec4(0.0, 1.0, -front.y/front.z, 1.0));
    vec4 right = normalize(vec4(cross(vec3(up), vec3(front)), 1.0));

    gl_Position = projection*(gl_in[i].gl_Position);
    EmitVertex();
    gl_Position = projection*(gl_in[i].gl_Position + up);
    EmitVertex();
    EndPrimitive();

    gl_Position = projection*(gl_in[i].gl_Position);
    EmitVertex();
    gl_Position = projection*(gl_in[i].gl_Position - up);
    EmitVertex();
    EndPrimitive();

    gl_Position = projection*(gl_in[i].gl_Position);
    EmitVertex();
    gl_Position = projection*(gl_in[i].gl_Position + 4*front);
    EmitVertex();
    EndPrimitive();

    gl_Position = projection*(gl_in[i].gl_Position);
    EmitVertex();
    gl_Position = projection*(gl_in[i].gl_Position - front);
    EmitVertex();
    EndPrimitive();

    gl_Position = projection*(gl_in[i].gl_Position);
    EmitVertex();
    gl_Position = projection*(gl_in[i].gl_Position + right);
    EmitVertex();
    EndPrimitive();

    gl_Position = projection*(gl_in[i].gl_Position);
    EmitVertex();
    gl_Position = projection*(gl_in[i].gl_Position - right);
    EmitVertex();
    EndPrimitive();
    }
}
