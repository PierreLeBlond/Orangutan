in vec2 uv_out;
in vec3 spec_out;
in vec3 diffuseAndAmbient_out;

uniform sampler2D colorMap;

uniform int nbDiffuseMap;

out vec4 color_out;

void main()
{
    vec4 c = texture(colorMap, uv_out);
    color_out = vec4((diffuseAndAmbient_out + spec_out)*c.rgb, c.a);
}
