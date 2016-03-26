/**
 * \file renderable.cpp
 * \brief Sources de la classe d'objet.
 * \author Pierre Lespingal
 * \version 1.0
 * \date 20 fevrier 2015
 *
 * Classe de representation d'objet
 * Un objet est le regroupement d'une structure 3D, de matériaux et de textures, d'une matrice modele et d'autres propriétés.
 *
 */

#include "renderable.h"


Renderer::Renderer() :_mesh(0)
{
    OpenGLFunction::functions().glGenVertexArrays(1, &_vao);

    OpenGLFunction::functions().glGenBuffers(1, &_idOfPositionArray);
    OpenGLFunction::functions().glGenBuffers(1, &_idOfNormalArray);
    OpenGLFunction::functions().glGenBuffers(1, &_idOfTexCoordArray);
    OpenGLFunction::functions().glGenBuffers(1, &_idOfIndexArray);
}

Renderer::~Renderer()
{ 
    OpenGLFunction::functions().glDeleteBuffers(1, &_idOfPositionArray);
    OpenGLFunction::functions().glDeleteBuffers(1, &_idOfNormalArray);
    OpenGLFunction::functions().glDeleteBuffers(1, &_idOfTexCoordArray);
    OpenGLFunction::functions().glDeleteBuffers(1, &_idOfIndexArray);

    OpenGLFunction::functions().glDeleteVertexArrays(1, &_vao);
}

/**
 * @brief Renderable::createVertexArrayObject
 * To call whenever the material or the shader strategy have changed
 */
void Renderer::createVertexArrayObject()
{
    if(_mesh)
    {
        OpenGLFunction::functions().glBindVertexArray(_vao);
        OpenGLFunction::functions().glEnableVertexAttribArray(_material.getShaderStrategy()->getVertexAttribute());
        OpenGLFunction::functions().glEnableVertexAttribArray(_material.getShaderStrategy()->getNormalAttribute());
        OpenGLFunction::functions().glEnableVertexAttribArray(_material.getShaderStrategy()->getTextureCoordinateAttribute());

        OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, _idOfPositionArray);
        OpenGLFunction::functions().glVertexAttribPointer(_material.getShaderStrategy()->getVertexAttribute(), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, _idOfNormalArray);
        OpenGLFunction::functions().glVertexAttribPointer(_material.getShaderStrategy()->getNormalAttribute(), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, _idOfTexCoordArray);
        OpenGLFunction::functions().glVertexAttribPointer(_material.getShaderStrategy()->getTextureCoordinateAttribute(), 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        OpenGLFunction::functions().glBindVertexArray(0);
    }
}

void Renderer::fillInVBO()
{
    if(_mesh)
    {
        OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, _idOfPositionArray);
        OpenGLFunction::functions().glBufferData(GL_ARRAY_BUFFER, 3 * _mesh->getNumberOfVertices() * sizeof(GLfloat), _mesh->getPositions(), GL_STATIC_DRAW);

        OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, _idOfNormalArray);
        OpenGLFunction::functions().glBufferData(GL_ARRAY_BUFFER, 3 * _mesh->getNumberOfNormals() * sizeof(GLfloat), _mesh->getNormals(), GL_STATIC_DRAW);

        OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, _idOfTexCoordArray);
        OpenGLFunction::functions().glBufferData(GL_ARRAY_BUFFER, 2 * _mesh->getNumberOfTexCoords() * sizeof(GLfloat), _mesh->getTexCoords(), GL_STATIC_DRAW);

        OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idOfIndexArray);
        OpenGLFunction::functions().glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * _mesh->getNumberOfTriangles() * sizeof(GLuint), _mesh->getIndexes(), GL_STATIC_DRAW);

        OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, 0);
        OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void Renderer::draw(const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<LightNode> > &lights)
{
    if(_mesh) {
    _transform.update();
    _material.getShaderStrategy()->draw(_vao, _idOfIndexArray, *_mesh, _material, modelMatrix*_transform.getModelMatrix(), viewMatrix, projectionMatrix, lights);
    }
}

void Renderer::setMesh(std::shared_ptr<const Mesh> mesh){
    _mesh = mesh;
}

void Renderer::setMaterial(const Material &material){
    _material = material;
}

const Transform& Renderer::getTransform() const{
    return _transform;
}

const Material& Renderer::getMaterial() const{
    return _material;
}

GLuint Renderer::getIdOfPositionArray() const{
    return _idOfPositionArray;
}

GLuint Renderer::getIdOfIndexArray() const{
    return _idOfIndexArray;
}

GLuint Renderer::getIdOfNormalArray() const{
    return _idOfNormalArray;
}

GLuint Renderer::getIdOfTexCoordArray() const{
    return _idOfTexCoordArray;
}

GLuint Renderer::getVao() const{
    return _vao;
}

//inherit from Materiable



const ShaderStrategy *Renderer::getShaderStrategy() const{
    return _material.getShaderStrategy();
}

GLuint Renderer::getColorMapId() const{
    return _material.getColorMapId();
}

GLuint Renderer::getCubeMapId() const{
    return _material.getCubeMapId();
}

GLuint Renderer::getRenderMapId() const{
    return _material.getRenderMapId();
}

QColor Renderer::getColor() const{
    return _material.getColor();
}

glm::vec3 Renderer::getKd() const{
    return _material.getKd();
}

glm::vec3 Renderer::getKa() const{
    return _material.getKa();
}

glm::vec3 Renderer::getKs() const{
    return _material.getKs();
}

GLfloat Renderer::getTr() const{
    return _material.getTr();
}

GLfloat Renderer::getNs() const{
    return _material.getNs();
}

GLfloat Renderer::getRefractionRatio() const{
    return _material.getRefractionRatio();
}

GLfloat Renderer::getReflexionPercentage() const{
    return _material.getReflexionPercentage();
}

GLfloat Renderer::getEdgeFilterThreshold() const{
    return _material.getEdgeFilterThreshold();
}

void Renderer::setShaderStrategy(const ShaderStrategy *shaderStrategy){
    _material.setShaderStrategy(shaderStrategy);
}

void Renderer::setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) {
    _material.setMtl(Kd, Ks, Ka, Ns, Tr);
}

void Renderer::setColorMapId(GLuint id){
    _material.setColorMapId(id);
}

void Renderer::setCubeMapId(GLuint id){
    _material.setCubeMapId(id);
}

void Renderer::setRenderMapId(GLuint id){
    _material.setRenderMapId(id);
}

void Renderer::setColor(QColor color){
    _material.setColor(color);
}

void Renderer::setKd(float Kd){
    _material.setKd(Kd);
}

void Renderer::setKa(float Ka){
    _material.setKa(Ka);
}

void Renderer::setKs(float Ks){
    _material.setKs(Ks);
}

void Renderer::setNs(float Ns){
    _material.setNs(Ns);
}

void Renderer::setRefractionRatio(float ratio){
    _material.setRefractionRatio(ratio);
}

void Renderer::setReflexionPercentage(float percentage){
    _material.setReflexionPercentage(percentage);
}

void Renderer::setEdgeFilterThreshold(float threshold){
    _material.setEdgeFilterThreshold(threshold);
}

//inherit from Transformable
void Renderer::setModelMatrix(const glm::mat4& modelMatrix){
    _transform.setModelMatrix(modelMatrix);
}

void Renderer::setXRotation(float angle){
    _transform.setXRotation(angle);
}

void Renderer::setYRotation(float angle){
    _transform.setYRotation(angle);
}

void Renderer::setZRotation(float angle){
    _transform.setZRotation(angle);
}

void Renderer::setXScale(float scale){
    _transform.setXScale(scale);
}

void Renderer::setYScale(float scale){
    _transform.setYScale(scale);
}

void Renderer::setZScale(float scale){
    _transform.setZScale(scale);
}

void Renderer::setXPos(int x){
    _transform.setXPos(x);
}

void Renderer::setXPos(float x){
    _transform.setXPos(x);
}

void Renderer::setYPos(int y){
    _transform.setYPos(y);
}

void Renderer::setYPos(float y){
    _transform.setYPos(y);
}

void Renderer::setZPos(int z){
    _transform.setZPos(z);
}

void Renderer::setZPos(float z){
    _transform.setZPos(z);
}

void Renderer::setTranslationMatrix(const glm::vec3& vector){
    _transform.setTranslationMatrix(vector);
}

void Renderer::move(int direction){
    _transform.move(direction);
}

void Renderer::animate(){
    _transform.animate();
}

void Renderer::update(){
    _transform.update();
}

void Renderer::setXRotationSpeed(float speed){
    _transform.setXRotationSpeed(speed);
}

void Renderer::setYRotationSpeed(float speed){
    _transform.setYRotationSpeed(speed);
}

void Renderer::setZRotationSpeed(float speed){
    _transform.setZRotationSpeed(speed);
}

void Renderer::setXTranslationSpeed(float speed){
    _transform.setXTranslationSpeed(speed);
}

void Renderer::setYTranslationSpeed(float speed){
    _transform.setYTranslationSpeed(speed);
}

void Renderer::setZTranslationSpeed(float speed){
    _transform.setZTranslationSpeed(speed);
}

void Renderer::setXTranslationSmallAxe(int l){
    _transform.setXTranslationSmallAxe(l);
}

void Renderer::setYTranslationSmallAxe(int l){
    _transform.setYTranslationSmallAxe(l);
}

void Renderer::setZTranslationSmallAxe(int l){
    _transform.setZTranslationSmallAxe(l);
}

void Renderer::setXTranslationBigAxe(int l){
    _transform.setXTranslationBigAxe(l);
}

void Renderer::setYTranslationBigAxe(int l){
    _transform.setYTranslationBigAxe(l);
}

void Renderer::setZTranslationBigAxe(int l){
    _transform.setZTranslationBigAxe(l);
}
