#ifndef GOURAUDSTRATEGY_H
#define GOURAUDSTRATEGY_H

#include "shaderstrategy.h"

class GouraudStrategy : public ShaderStrategy
{
public:
                                                GouraudStrategy();
                                                ~GouraudStrategy();
    virtual void                                draw(GLuint vao, GLuint idOfIndexArray, const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::vector<std::shared_ptr<LightNode>>& lights) const;
    virtual void                                initAttribute();
    virtual void                                initUniformLocation();

private :

    GLuint                                      _indexOfProjectionMatrix;
    GLuint                                      _indexOfViewMatrix;
    GLuint                                      _indexOfModelMatrix;

    GLuint                                      _indexOfColorMap;

    GLuint                                      _indexOfKs;
    GLuint                                      _indexOfKa;
    GLuint                                      _indexOfNs;
    GLuint                                      _indexOfKd;

    GLuint                                      _indexOfNbPonctualLight;
    GLuint                                      _indexOfNbAmbiantLight;
    GLuint                                      _indexOfNbDirectionLight;
    GLuint                                      _indexOfNbSpotLight;

    std::vector<GLuint>                         _indexOfPonctualLightPositionLocation;
    std::vector<GLuint>                         _indexOfPonctualLightLaLocation;
    std::vector<GLuint>                         _indexOfPonctualLightLsLocation;
    std::vector<GLuint>                         _indexOfPonctualLightLdLocation;

    std::vector<GLuint>                         _indexOfAmbientLightLaLocation;

    std::vector<GLuint>                         _indexOfDirectionalLightPositionLocation;
    std::vector<GLuint>                         _indexOfDirectionalLightDirectionLocation;
    std::vector<GLuint>                         _indexOfDirectionalLightLaLocation;
    std::vector<GLuint>                         _indexOfDirectionalLightLsLocation;
    std::vector<GLuint>                         _indexOfDirectionalLightLdLocation;

    std::vector<GLuint>                         _indexOfSpotLightPositionLocation;
    std::vector<GLuint>                         _indexOfSpotLightDirectionLocation;
    std::vector<GLuint>                         _indexOfSpotLightLaLocation;
    std::vector<GLuint>                         _indexOfSpotLightLsLocation;
    std::vector<GLuint>                         _indexOfSpotLightLdLocation;
    std::vector<GLuint>                         _indexOfSpotLightExponentLocation;
    std::vector<GLuint>                         _indexOfSpotLightCutoffLocation;
};

#endif // GOURAUDSTRATEGY_H
