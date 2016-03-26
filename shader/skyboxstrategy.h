#ifndef SKYBOXSTRATEGY_H
#define SKYBOXSTRATEGY_H

#include "shaderstrategy.h"

class SkyboxStrategy : public ShaderStrategy
{
public:
    SkyboxStrategy();
    ~SkyboxStrategy();
    virtual void                                draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material &material, const glm::core::type::mat4& modelMatrix, const glm::core::type::mat4& viewMatrix, const glm::core::type::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>> &lights) const;
    virtual void                                initAttribute();
    virtual void                                initUniformLocation();

private :

    GLuint                                      _indexOfProjectionMatrix;
    GLuint                                      _indexOfViewMatrix;
    GLuint                                      _indexOfModelMatrix;

    GLuint                                      _indexOfLa;
    GLuint                                      _indexOfDiffuseMap;
};

#endif // SKYBOXSTRATEGY_H
