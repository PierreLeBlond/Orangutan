#include "object/renderableobject.h"
#include "core/debug.h"

RenderableObject::RenderableObject(const std::string& name) :
    Object(name),
    _mesh(0)
{
    _idOfPositionArray = _vao.addBuffer();
    _idOfNormalArray = _vao.addBuffer();
    _idOfTexCoordArray = _vao.addBuffer();
}

void RenderableObject::initVertexArrayObject()
{
    if(_shaderMaterial.getShaderStrategy()->getVertexAttribute() > -1)
        _vao.attribBuffer(_idOfPositionArray,
                          _shaderMaterial.getShaderStrategy()->getVertexAttribute(),
                          3, O_FLOAT);
    if(_shaderMaterial.getShaderStrategy()->getNormalAttribute() > -1)
        _vao.attribBuffer(_idOfNormalArray,
                          _shaderMaterial.getShaderStrategy()->getNormalAttribute(),
                          3, O_FLOAT);
    if(_shaderMaterial.getShaderStrategy()->getTextureCoordinateAttribute() > -1)
        _vao.attribBuffer(_idOfTexCoordArray,
                          _shaderMaterial.getShaderStrategy()->getTextureCoordinateAttribute(),
                          2, O_FLOAT);
}

void RenderableObject::fillInVBO()
{
    if(_shaderMaterial.getShaderStrategy()->getVertexAttribute() > -1)
        _vao.fillBuffer(_idOfPositionArray,
                        _mesh->getNumberOfPositions() * sizeof(float),
                        _mesh->getPositions().data());
    if(_shaderMaterial.getShaderStrategy()->getNormalAttribute() > -1)
        _vao.fillBuffer(_idOfNormalArray,
                        _mesh->getNumberOfNormals() * sizeof(float),
                        _mesh->getNormals().data());
    if(_shaderMaterial.getShaderStrategy()->getTextureCoordinateAttribute() > -1)
        _vao.fillBuffer(_idOfTexCoordArray,
                        _mesh->getNumberOfUvs() * sizeof(float),
                        _mesh->getUvs().data());
    _vao.fillIndexBuffer(_mesh->getNumberOfFaces() * sizeof(int),
                         _mesh->getFaces().data());
    _vao.setNumberOfElements(3 * _mesh->getNumberOfFaces());
}

void RenderableObject::draw(const glm::core::type::mat4 &viewMatrix, const glm::core::type::mat4 &projectionMatrix, const std::vector<std::shared_ptr<Light> > &lights)
{
    _shaderMaterial.getShaderStrategy()->setUniforms(_shaderMaterial
                                                     , getTransform().getGlobalMatrix()
                                                     * getTransform().getModelMatrix()
                                                     , viewMatrix
                                                     , projectionMatrix
                                                     , lights);
    _shaderMaterial.getShaderStrategy()->draw(_vao);
}

void RenderableObject::setMesh(std::shared_ptr<const Mesh> mesh){
    _mesh = mesh;
}

void RenderableObject::setShaderMaterial(const ShaderMaterial &shaderMaterial){
    _shaderMaterial = shaderMaterial;
}

const ShaderMaterial& RenderableObject::getShaderMaterial() const{
    return _shaderMaterial;
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

//inherite from ShaderMaterialable
std::shared_ptr<const ShaderStrategy> RenderableObject::getShaderStrategy() const
{
    return _shaderMaterial.getShaderStrategy();
}

void RenderableObject::setShaderStrategy(std::shared_ptr<const ShaderStrategy>
                                         shaderStrategy)
{
    _shaderMaterial.setShaderStrategy(shaderStrategy);
}

bool RenderableObject::setTexture(const std::string& name,
                                  std::shared_ptr<DDTexture> texture)
{
    return _shaderMaterial.setTexture(name, texture);
}

bool RenderableObject::setCubeTexture(const std::string& name,
                                      std::shared_ptr<CubeTexture> texture)
{
    return _shaderMaterial.setCubeTexture(name, texture);
}

void RenderableObject::addMaterial(Material m)
{
    _shaderMaterial.addMaterial(m);
}
