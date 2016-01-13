#version 330

in vec2 uv_out;
in vec3 spec_out;
in vec3 diffuseAndAmbient_out;

uniform sampler2D firstDiffuseMap;
uniform sampler2D secondDiffuseMap;
uniform sampler2D thirdDiffuseMap;

uniform int nbDiffuseMap;

out vec4 color_out;

void main()
{
    vec4 d[3];
    d[0] = texture(firstDiffuseMap, uv_out);
    d[1] = texture(secondDiffuseMap, uv_out);
    d[2] = texture(thirdDiffuseMap, uv_out);

    vec4 c = vec4(1.0);
    for(int i = 0; i < nbDiffuseMap;i++){
        c = mix(c, d[i], d[i].a);
    }

    color_out = vec4((diffuseAndAmbient_out + spec_out)*c.rgb, c.a);
}
