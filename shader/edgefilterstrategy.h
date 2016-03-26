#ifndef EDGEFILTERSTRATEGY_H
#define EDGEFILTERSTRATEGY_H

#include "shaderstrategy.h"


class EdgeFilterStrategy : public ShaderStrategy
{
public:
                                    EdgeFilterStrategy();
    virtual void                    draw(GLuint vao, GLuint idOfIndexArray, const Mesh &mesh, const Material &material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights) const;
    virtual void                    initAttribute();
    virtual void                    initUniformLocation();

private:
    GLuint                          _indexOfProjectionMatrix;
    GLuint                          _indexOfViewMatrix;
    GLuint                          _indexOfModelMatrix;

    GLuint                          _indexOfRenderTex;
    GLuint                          _indexOfEdgeThreshold;
};

#endif // EDGEFILTERSTRATEGY_H
