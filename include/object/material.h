#pragma once

#include "core/texture.h"
#include "object/object.h"
#include "object/asset.h"
#include "shader/shaderstrategy.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include <fstream>
#include <memory>

class ShaderStrategy;

class Materialable
{
public:

    virtual std::shared_ptr<const ShaderStrategy>   getShaderStrategy() const = 0;
    virtual unsigned int                            getColorMapId() const = 0;
    virtual unsigned int                            getCubeMapId() const = 0;
    virtual unsigned int                            getRenderMapId() const = 0;

    virtual glm::vec4                               getColor() const = 0;
    virtual glm::vec3                               getKd() const = 0;
    virtual glm::vec3                               getKa() const = 0;
    virtual glm::vec3                               getKs() const = 0;
    virtual float                                   getTr() const = 0;
    virtual float                                   getNs() const = 0;
    virtual float                                   getRefractionRatio() const = 0;
    virtual float                                   getReflexionPercentage() const = 0;
    virtual float                                   getEdgeFilterThreshold() const = 0;

    virtual void                                    setShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy) = 0;

    virtual void                                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) = 0;

    virtual void                                    setColorMapId(unsigned int id) = 0;
    virtual void                                    setCubeMapId(unsigned int id) = 0;
    virtual void                                    setRenderMapId(unsigned int id) = 0;

    virtual void                                    setColor(glm::vec4 color) = 0;
    virtual void                                    setKd(float Kd) = 0;
    virtual void                                    setKa(float Ka) = 0;
    virtual void                                    setKs(float Ks) = 0;
    virtual void                                    setNs(float Ns) = 0;
    virtual void                                    setRefractionRatio(float ratio) = 0;
    virtual void                                    setReflexionPercentage(float percentage) = 0;
    virtual void                                    setEdgeFilterThreshold(float threshold) = 0;
};

class Material : public Asset, public Materialable
{
public:
                                                    Material(std::string name = "untitled");

    virtual std::shared_ptr<const ShaderStrategy>   getShaderStrategy() const;

    virtual unsigned int                            getColorMapId()	const;
    virtual unsigned int                            getCubeMapId() const;
    virtual unsigned int                            getRenderMapId() const;

    virtual glm::vec4                               getColor() const;
    virtual glm::vec3                               getKd() const;
    virtual glm::vec3                               getKa() const;
    virtual glm::vec3                               getKs() const;
    virtual float                                   getTr() const;
    virtual float                                   getNs() const;
    virtual float                                   getRefractionRatio() const;
    virtual float                                   getReflexionPercentage() const;

    virtual float                                   getEdgeFilterThreshold() const;

    virtual void                                    setShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy);

    virtual void                                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr);

    virtual void                                    setColorMapId(unsigned int id);
    virtual void                                    setCubeMapId(unsigned int id);
    virtual void                                    setRenderMapId(unsigned int id);

    virtual void                                    setColor(glm::vec4 color);
    virtual void                                    setKd(float Kd);
    virtual void                                    setKa(float Ka);
    virtual void                                    setKs(float Ks);
    virtual void                                    setNs(float Ns);
    virtual void                                    setRefractionRatio(float ratio);
    virtual void                                    setReflexionPercentage(float percentage);

    virtual void                                    setEdgeFilterThreshold(float threshold);


private:
    unsigned int                                    _colorMapId;
    unsigned int                                    _cubeMapId;
    unsigned int                                    _renderMapId;


    glm::vec3                                       _Kd;
    glm::vec3                                       _Ks;
    glm::vec3                                       _Ka;
    unsigned int                                    _illum;
    float                                           _Ns;
    float                                           _Tr;
    glm::vec4                                       _color;

    float                                           _refractionRatio;
    float                                           _reflexionPercentage;

    float                                           _edgeFilterThreshold;

    std::shared_ptr<const ShaderStrategy>           _shaderStrategy;
};
