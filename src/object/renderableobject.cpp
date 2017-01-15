#include "object/renderableobject.h"
#include "core/debug.h"

RenderableObject::RenderableObject() : _mesh(0)
{
    _idOfPositionArray = _vao.addBuffer();
    _idOfNormalArray = _vao.addBuffer();
    _idOfTexCoordArray = _vao.addBuffer();
}

RenderableObject::~RenderableObject()
{
}

void RenderableObject::createVertexArrayObject()
{
    _vao.bind();
    if(_material.getShaderStrategy()->getVertexAttribute() > -1)
        _vao.attribBuffer(_idOfPositionArray, _material.getShaderStrategy()->getVertexAttribute(), 3, O_FLOAT);
    if(_material.getShaderStrategy()->getNormalAttribute() > -1)
        _vao.attribBuffer(_idOfNormalArray, _material.getShaderStrategy()->getNormalAttribute(), 3, O_FLOAT);
    if(_material.getShaderStrategy()->getTextureCoordinateAttribute() > -1)
        _vao.attribBuffer(_idOfTexCoordArray, _material.getShaderStrategy()->getTextureCoordinateAttribute(), 2, O_FLOAT);

    _vao.unbind();
}

void RenderableObject::fillInVBO()
{
    if(_material.getShaderStrategy()->getVertexAttribute() > -1)
        _vao.fillBuffer(_idOfPositionArray, 3 * _mesh->getNumberOfVertices() * sizeof(float), _mesh->getPositions());
    if(_material.getShaderStrategy()->getNormalAttribute() > -1)
        _vao.fillBuffer(_idOfNormalArray, 3 * _mesh->getNumberOfNormals() * sizeof(float), _mesh->getNormals());
    if(_material.getShaderStrategy()->getTextureCoordinateAttribute() > -1)
        _vao.fillBuffer(_idOfTexCoordArray, 2 * _mesh->getNumberOfTexCoords() * sizeof(float), _mesh->getTexCoords());
        _vao.fillIndexBuffer(3 * _mesh->getNumberOfTriangles() * sizeof(int), _mesh->getIndexes());
        _vao.setNumberOfElements(3 * _mesh->getNumberOfTriangles());
}

void RenderableObject::draw(const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<Light> > &lights)
{
    _material.getShaderStrategy()->setUniform(_material, getTransform().getGlobalMatrix()*getTransform().getModelMatrix(), viewMatrix, projectionMatrix, lights);
    _material.getShaderStrategy()->draw(_vao);
}

void RenderableObject::setMesh(std::shared_ptr<const Mesh> mesh){
    _mesh = mesh;
}

void RenderableObject::setMaterial(const Material &material){
    _material = material;
}

const Material& RenderableObject::getMaterial() const{
    return _material;
}

unsigned int RenderableObject::getIdOfPositionArray() const{
    return _idOfPositionArray;
}

unsigned int RenderableObject::getIdOfIndexArray() const{
    return _idOfIndexArray;
}

unsigned int RenderableObject::getIdOfNormalArray() const{
    return _idOfNormalArray;
}

unsigned int RenderableObject::getIdOfTexCoordArray() const{
    return _idOfTexCoordArray;
}

const Vao& RenderableObject::getVao() const{
    return _vao;
}

//inherit from Materiable
std::shared_ptr<const ShaderStrategy> RenderableObject::getShaderStrategy() const{
    return _material.getShaderStrategy();
}

unsigned int RenderableObject::getColorMapId() const{
    return _material.getColorMapId();
}

unsigned int RenderableObject::getCubeMapId() const{
    return _material.getCubeMapId();
}

unsigned int RenderableObject::getRenderMapId() const{
    return _material.getRenderMapId();
}

glm::vec4 RenderableObject::getColor() const{
    return _material.getColor();
}

glm::vec3 RenderableObject::getKd() const{
    return _material.getKd();
}

glm::vec3 RenderableObject::getKa() const{
    return _material.getKa();
}

glm::vec3 RenderableObject::getKs() const{
    return _material.getKs();
}

float RenderableObject::getTr() const{
    return _material.getTr();
}

float RenderableObject::getNs() const{
    return _material.getNs();
}

float RenderableObject::getRefractionRatio() const{
    return _material.getRefractionRatio();
}

float RenderableObject::getReflexionPercentage() const{
    return _material.getReflexionPercentage();
}

float RenderableObject::getEdgeFilterThreshold() const{
    return _material.getEdgeFilterThreshold();
}

void RenderableObject::setShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy){
    _material.setShaderStrategy(shaderStrategy);
}

void RenderableObject::setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) {
    _material.setMtl(Kd, Ks, Ka, Ns, Tr);
}

void RenderableObject::setColorMapId(unsigned int id){
    _material.setColorMapId(id);
}

void RenderableObject::setCubeMapId(unsigned int id){
    _material.setCubeMapId(id);
}

void RenderableObject::setRenderMapId(unsigned int id){
    _material.setRenderMapId(id);
}

void RenderableObject::setColor(glm::vec4 color){
    _material.setColor(color);
}

void RenderableObject::setKd(float Kd){
    _material.setKd(Kd);
}

void RenderableObject::setKa(float Ka){
    _material.setKa(Ka);
}

void RenderableObject::setKs(float Ks){
    _material.setKs(Ks);
}

void RenderableObject::setNs(float Ns){
    _material.setNs(Ns);
}

void RenderableObject::setRefractionRatio(float ratio){
    _material.setRefractionRatio(ratio);
}

void RenderableObject::setReflexionPercentage(float percentage){
    _material.setReflexionPercentage(percentage);
}

void RenderableObject::setEdgeFilterThreshold(float threshold){
    _material.setEdgeFilterThreshold(threshold);
}
