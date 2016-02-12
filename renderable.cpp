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


Renderable::Renderable() :_mesh(0)
{
    OpenGLFunction::functions().glGenVertexArrays(1, &_vao);

    OpenGLFunction::functions().glGenBuffers(1, &_idOfPositionArray);
    OpenGLFunction::functions().glGenBuffers(1, &_idOfNormalArray);
    OpenGLFunction::functions().glGenBuffers(1, &_idOfTexCoordArray);
    OpenGLFunction::functions().glGenBuffers(1, &_idOfIndexArray);
}

Renderable::~Renderable()
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
void Renderable::createVertexArrayObject()
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

void Renderable::fillInVBO()
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

void Renderable::draw(const glm::core::type::mat4 &modelMatrix, const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<LightNode> > &lights)
{
    if(_mesh) {
    _transform.update();
    _material.getShaderStrategy()->draw(_vao, _idOfIndexArray, *_mesh, _material, modelMatrix*_transform.getModelMatrix(), viewMatrix, projectionMatrix, lights);
    }
}

void Renderable::setMesh(std::shared_ptr<const Mesh> mesh){
    _mesh = mesh;
}

//inherit from Materiable



const ShaderStrategy *Renderable::getShaderStrategy() const{
    return _material.getShaderStrategy();
}

std::shared_ptr<const Texture> Renderable::getColorMap() const{
    return _material.getColorMap();
}

GLuint Renderable::getCubeMapId() const{
    return _material.getCubeMapId();
}

QColor Renderable::getColor() const{
    return _material.getColor();
}

glm::vec3 Renderable::getKd() const{
    return _material.getKd();
}

glm::vec3 Renderable::getKa() const{
    return _material.getKa();
}

glm::vec3 Renderable::getKs() const{
    return _material.getKs();
}

GLfloat Renderable::getTr() const{
    return _material.getTr();
}

GLfloat Renderable::getNs() const{
    return _material.getNs();
}

GLfloat Renderable::getRefractionRatio() const{
    return _material.getRefractionRatio();
}

GLfloat Renderable::getReflexionPercentage() const{
    return _material.getReflexionPercentage();
}

void Renderable::setShaderStrategy(const ShaderStrategy *shaderStrategy){
    _material.setShaderStrategy(shaderStrategy);
}

void Renderable::setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) {
    _material.setMtl(Kd, Ks, Ka, Ns, Tr);
}

void Renderable::setColorMap(std::shared_ptr<const Texture> texture){
    _material.setColorMap(texture);
}

void Renderable::CreateCubeMap(){
    _material.CreateCubeMap();
}

void Renderable::setCubeMapId(GLuint id){
    _material.setCubeMapId(id);
}

void Renderable::setColor(QColor color){
    _material.setColor(color);
}

void Renderable::setKd(float Kd){
    _material.setKd(Kd);
}

void Renderable::setKa(float Ka){
    _material.setKa(Ka);
}

void Renderable::setKs(float Ks){
    _material.setKs(Ks);
}

void Renderable::setNs(float Ns){
    _material.setNs(Ns);
}

void Renderable::setRefractionRatio(float ratio){
    _material.setRefractionRatio(ratio);
}

void Renderable::setReflexionPercentage(float percentage){
    _material.setReflexionPercentage(percentage);
}

//inherit from Transformable
void Renderable::setModelMatrix(const glm::mat4& modelMatrix){
    _transform.setModelMatrix(modelMatrix);
}

void Renderable::setXRotation(float angle){
    _transform.setXRotation(angle);
}

void Renderable::setYRotation(float angle){
    _transform.setYRotation(angle);
}

void Renderable::setZRotation(float angle){
    _transform.setZRotation(angle);
}

void Renderable::setXScale(float scale){
    _transform.setXScale(scale);
}

void Renderable::setYScale(float scale){
    _transform.setYScale(scale);
}

void Renderable::setZScale(float scale){
    _transform.setZScale(scale);
}

void Renderable::setXPos(int x){
    _transform.setXPos(x);
}

void Renderable::setXPos(float x){
    _transform.setXPos(x);
}

void Renderable::setYPos(int y){
    _transform.setYPos(y);
}

void Renderable::setYPos(float y){
    _transform.setYPos(y);
}

void Renderable::setZPos(int z){
    _transform.setZPos(z);
}

void Renderable::setZPos(float z){
    _transform.setZPos(z);
}

void Renderable::setTranslationMatrix(const glm::vec3& vector){
    _transform.setTranslationMatrix(vector);
}

void Renderable::move(int direction){
    _transform.move(direction);
}

void Renderable::animate(){
    _transform.animate();
}

void Renderable::update(){
    _transform.update();
}

void Renderable::setXRotationSpeed(float speed){
    _transform.setXRotationSpeed(speed);
}

void Renderable::setYRotationSpeed(float speed){
    _transform.setYRotationSpeed(speed);
}

void Renderable::setZRotationSpeed(float speed){
    _transform.setZRotationSpeed(speed);
}

void Renderable::setXTranslationSpeed(float speed){
    _transform.setXTranslationSpeed(speed);
}

void Renderable::setYTranslationSpeed(float speed){
    _transform.setYTranslationSpeed(speed);
}

void Renderable::setZTranslationSpeed(float speed){
    _transform.setZTranslationSpeed(speed);
}

void Renderable::setXTranslationSmallAxe(int l){
    _transform.setXTranslationSmallAxe(l);
}

void Renderable::setYTranslationSmallAxe(int l){
    _transform.setYTranslationSmallAxe(l);
}

void Renderable::setZTranslationSmallAxe(int l){
    _transform.setZTranslationSmallAxe(l);
}

void Renderable::setXTranslationBigAxe(int l){
    _transform.setXTranslationBigAxe(l);
}

void Renderable::setYTranslationBigAxe(int l){
    _transform.setYTranslationBigAxe(l);
}

void Renderable::setZTranslationBigAxe(int l){
    _transform.setZTranslationBigAxe(l);
}
