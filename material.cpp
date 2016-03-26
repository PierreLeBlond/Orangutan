#include "material.h"


Material::Material(std::string name) : _name(name), _colorMapId(-1), _renderMapId(-1),
    _Kd(glm::vec3(1.0f)), _Ks(glm::vec3(1.0f)), _Ka(glm::vec3(1.0f)),
    _illum(1), _Ns(10.0f), _Tr(1.0f), _color(QColor::fromRgb(255, 255, 255)),
    _refractionRatio(0), _reflexionPercentage(100), _edgeFilterThreshold(0.7) {
}

const ShaderStrategy *Material::getShaderStrategy() const{
    return _shaderStrategy;
}

GLuint Material::getColorMapId() const{
    return _colorMapId;
}

GLuint Material::getCubeMapId() const{
    return _cubeMapId;
}

GLuint Material::getRenderMapId() const{
    return _renderMapId;
}

QColor Material::getColor() const{
    return _color;
}

glm::vec3 Material::getKd() const{
    return _Kd;
}

glm::vec3 Material::getKa() const{
    return _Ka;
}

glm::vec3 Material::getKs() const{
    return _Ks;
}

GLfloat Material::getTr() const{
    return _Tr;
}

GLfloat Material::getNs() const{
    return _Ns;
}

GLfloat Material::getRefractionRatio() const{
    return _refractionRatio;
}

GLfloat Material::getReflexionPercentage() const{
    return _reflexionPercentage;
}

GLfloat Material::getEdgeFilterThreshold() const{
    return _edgeFilterThreshold;
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

void Material::setColorMapId(GLuint id){
    _colorMapId = id;
}

void Material::setCubeMapId(GLuint id){
    _cubeMapId = id;
}

void Material::setRenderMapId(GLuint id){
    _renderMapId = id;
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

void Material::setEdgeFilterThreshold(float threshold){
    _edgeFilterThreshold = threshold;
}
