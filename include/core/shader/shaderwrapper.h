#ifndef SHADER_WRAPPER_H
#define SHADER_WRAPPER_H

#include <iostream>
#include <map>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "util/util.h"
#include "core/shader/shaderprogram.h"
#include "core/texture/texture.h"

#define MAX_LIGHT 8

class ShaderWrapper
{
public:
    void                                        storeUniformLocation();
    void                                        storeAttributeLocation();

    void                                        build(const std::string& vertexShaderPath,
                                                      const std::string& fragmentShaderPath,
                                                      const std::string& geometryShaderPath);

    void                                        start() const;
    void                                        stop() const;

    int                                         getUniformLocation(const std::string &name) const;
    std::vector<std::string>                    getUniformsName() const;
    int                                         getAttributeLocation(const std::string &name) const;

    template<typename T>
    void                                        setUniform(const std::string &structName, const std::string &name, const T &val)
    {
         std::ostringstream ost;
         ost << structName << "." << name;
         setUniform(ost.str(), val);
    }

    template<typename T>
    void                                        setUniform(const std::string &structName, int index, const std::string &name, const T &val)
    {
        std::ostringstream ost;
        ost << structName << "[" << index << "]." << name;
        setUniform(ost.str(), val);
    }

    template<typename T>
    void                                        setUniform(const std::string &name, int index, const T &val)
    {
        std::ostringstream ost;
        ost << name << "[" << index << "]";
        setUniform(ost.str(), val);
    }

    void                                        setUniform(const std::string &name, const glm::vec3 &v);
    void                                        setUniform(const std::string &name, const glm::vec4 &v);
    void                                        setUniform(const std::string &name, const glm::mat3 &m);
    void                                        setUniform(const std::string &name, const glm::mat4 &m);
    void                                        setUniform(const std::string &name, float val);
    void                                        setUniform(const std::string &name, int val);
    void                                        setUniform(const std::string &name, unsigned int val);
    void                                        setUniform(const std::string &name, bool val);

    void                                        bindTexture(const std::string &name, unsigned int id);
    void                                        bindCubeTexture(const std::string &name, unsigned int id);
    void                                        unbindTexture();

    unsigned int                                getProgramId() const;

private:
    ShaderProgram                               _shaderProgram;

    std::map<std::string, int>                  _uniformLocations;
    std::map<std::string, int>                  _attributeLocations;
};

#endif //SHADER_WRAPPER_H
