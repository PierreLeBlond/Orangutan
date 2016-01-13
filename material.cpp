#include "material.h"


Material::Material(std::string name) : _name(name),
    _ambientMapId(0), _diffuseMapId(0), _bumpMapId(0),
    _normalMapId(0), _specularMapId(0), _shininessMapId(0),
    _Kd(glm::vec3(1.0f)), _Ks(glm::vec3(1.0f)), _Ka(glm::vec3(1.0f)),
    _illum(1), _Ns(10.0f), _Tr(1.0f), _color(QColor::fromRgb(255, 255, 255)),
    _refractionRatio(0), _reflexionPercentage(100) {
_diffuseMapId = new Texture;
_diffuseMapId->addTexture(-1);
_diffuseMapId->addTexture(-1);
_diffuseMapId->addTexture(-1);
_normalMapId = new Texture;
}

Material::~Material() {
    delete _ambientMapId;
    delete _diffuseMapId;
    delete _bumpMapId;
    delete _normalMapId;
    delete _specularMapId;
    delete _shininessMapId;
}

const ShaderStrategy *Material::getShaderStrategy() const{
    return _shaderStrategy;
}

void Material::setShaderStrategy(const ShaderStrategy *shaderStrategy){
    _shaderStrategy = shaderStrategy;
}

void Material::setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) {
    _Kd = Kd;
    _Ks = Ks;
    _Ka = Ka;
    _Ns = Ns;
    _Tr = Tr;
}

void Material::setDiffuseMapId(Texture *texture){
    _diffuseMapId = texture;
}

void Material::setCubeMapId(GLuint id){
    _cubeMapId = id;
}

void Material::setColor(QColor color){
    _color = color;
}

void Material::setKd(float Kd){
    _Kd = glm::vec3(Kd);
}

void Material::setKa(float Ka){
    _Ka = glm::vec3(Ka);
}

void Material::setKs(float Ks){
    _Ks = glm::vec3(Ks);
}

void Material::setNs(float Ns){
    _Ns = Ns;
}

void Material::setRefractionRatio(float ratio){
    _refractionRatio = ratio;
}

void Material::setReflexionPercentage(float percentage){
    _reflexionPercentage = percentage;
}

void Material::CreateAmbientMap(const char* filename) {
    QImage image(filename);
    image.mirrored();
    GLuint id = Texture::createTexture(image);
    _ambientMapId->setTexture(id, 0);
}

void Material::CreateDiffuseMap(const char* filename)
{
    QImage image(filename);
    image.mirrored();
    GLuint id = Texture::createTexture(image);
    _diffuseMapId->setTexture(id, 0);
}

void Material::CreateBumpMap(const char* filename)
{
    QImage image(filename);
    image.mirrored();
    GLuint id = Texture::createTexture(image);
    _bumpMapId->setTexture(id, 0);
}

void Material::CreateNormalMap(const char* filename)
{
    QImage image(filename);
    image.mirrored();
    GLuint id = Texture::createTexture(image);
    _normalMapId->setTexture(id, 0);
}

void Material::CreateSpecularMap(const char* filename)
{
    QImage image(filename);
    image.mirrored();
    GLuint id = Texture::createTexture(image);
    _specularMapId->setTexture(id, 0);
}

void Material::CreateShininessMap(const char* filename)
{
    QImage image(filename);
    image.mirrored();
    GLuint id = Texture::createTexture(image);
    _shininessMapId->setTexture(id, 0);
}

void Material::CreateCubeMap()
{
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0 + 0);
    OpenGLFunction::functions().glEnable(GL_TEXTURE_CUBE_MAP);

    OpenGLFunction::functions().glGenTextures(1, &_cubeMapId);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapId);

    const char* suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz"};
    std::string baseFileName = "images/sky_";

    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };

    for(int i = 0;i < 6;i++)
    {
        std::string texName = baseFileName + suffixes[i] + ".png";
        QImage img(texName.c_str());
        img = img.rgbSwapped();
        OpenGLFunction::functions().glTexImage2D(targets[i], 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    }

    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    OpenGLFunction::functions().glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
