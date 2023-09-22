#define MAX_LIGHT 8

in vec3 vertex_in;
in vec3 normal_in;
in vec2 uv_in;

struct Lighting {
    vec4 position;
    vec3 direction;
    vec3 Ld;
    vec3 Ls;
    vec3 La;
    float exponent;
    float cutoff;
};

uniform Lighting ponctualLights[MAX_LIGHT];
uniform Lighting ambiantLights[MAX_LIGHT];
uniform Lighting directionalLights[MAX_LIGHT];
uniform Lighting spotLights[MAX_LIGHT];

uniform int nbPonctualLight;
uniform int nbAmbiantLight;
uniform int nbDirectionLight;
uniform int nbSpotLight;

uniform float Ns;
uniform vec3 Ks;
uniform vec3 Kd;
uniform vec3 Ka;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 uv_out;
out vec3 spec_out;
out vec3 diffuseAndAmbient_out;

vec3 adPhong(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    vec3 ambient = light.La*Ka;
    float sDotN = max(dot(s, normal), 0.0);
    vec3 diffuse = sDotN*Kd*light.Ld;
    return diffuse + ambient;
}

vec3 adPhongWithSpotLight(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    float angle = acos(dot(-s, light.direction));
    float cutoff = radians((min(max(light.cutoff, 0.0), 90.0)));

    vec3 ambient = light.La*Ka;

    if(angle < cutoff) {
        float spotFactor = pow(dot(-s, light.direction), light.exponent);
        return ambient + light.Ld * Kd * max(dot(s, normal), 0.0);
    } else {
        return vec3(0.0);
    }
}

vec3 sPhong(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    float sDotN = max(dot(s, normal), 0.0);
    vec3 spec = vec3(0.0);
    if(sDotN > 0.0)
        spec = light.Ls*Ks*pow(max(dot(r, v), 0.0), Ns);
    return spec;
}

vec3 sPhongWithSpotLight(Lighting light, vec3 s, vec3 v, vec3 r, vec3 normal)
{
    float scal = dot(-s, light.direction);
    float angle = acos(scal);
    float cutoff = radians((min(max(light.cutoff, 0), 90)));

    if(angle < cutoff) {
        float spotFactor = pow(scal, light.exponent);
        return spotFactor * light.Ls * Ks * pow(max(dot(r, normal), 0.0), Ns);
    } else {
        return vec3(0.0);
    }
}

void main()
{
    vec4 eyeCoords = viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
    vec3 v = normalize(-eyeCoords.xyz);

    vec3 normal = normalize( mat3(viewMatrix * modelMatrix) * normal_in);

    diffuseAndAmbient_out = vec3(0.0);
    spec_out = vec3(0.0);

    for(int i = 0; i < nbPonctualLight;i++){
        vec3 s = normalize(vec3(ponctualLights[i].position - eyeCoords));
        vec3 r = reflect(-s, normal);
       diffuseAndAmbient_out += adPhong(ponctualLights[i], s, v, r, normal);
       spec_out += sPhong(ponctualLights[i], s, v, r, normal);
    }

    for(int i = 0;i < nbAmbiantLight;i++){
        diffuseAndAmbient_out += ambiantLights[i].La*Ka;
    }

    for(int i = 0;i < nbDirectionLight;i++){
        vec3 s = normalize(directionalLights[i].direction);
        vec3 r = reflect(-s, normal);
       diffuseAndAmbient_out += adPhong(directionalLights[i], s, v, r, normal);
       spec_out += sPhong(directionalLights[i], s, v, r, normal);
    }

    for(int i = 0;i < nbSpotLight;i++){
        vec3 s = normalize(vec3(spotLights[i].position - eyeCoords));
        vec3 r = reflect(-s, normal);
        diffuseAndAmbient_out += adPhongWithSpotLight(spotLights[i], s, v, r, normal);
        spec_out += sPhongWithSpotLight(spotLights[i], s, v, r, normal);
    }

    uv_out = uv_in;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_in, 1.0);
}
