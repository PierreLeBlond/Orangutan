#pragma once

#include "core/shader.h"

#include "util/util.h"

#include "core/opengl.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/transform2.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <sstream>

#define MAX_LIGHT 8

class ShaderProgram
{
public:
                                                ShaderProgram();
                                                ~ShaderProgram();

    inline GLuint                               getProgramId()      const { return _programId; }
    inline const Shader&                        getVertexShader()   const { return _vertShader; }
    inline const Shader&                        getGeometryShader() const { return _geomShader; }
    inline const Shader&                        getFragmentShader() const { return _fragShader; }

    bool                                        initShader(const std::string &vert_location, const std::string &frag_location, const std::string &geom_location = "");
    void                                        storeUniformLocation();
    void                                        storeAttributeLocation();

    bool                                        attachGeometryShader();
    bool                                        attachVertexShader();
    bool                                        attachFragmentShader();
    bool                                        linkProgram();
    bool                                        detachFragmentShader();
    bool                                        detachVertexShader();
    bool                                        detachGeometryShader();

    void                                        startUseProgram() const { OpenGLFunction::functions().glUseProgram(_programId); }
    void                                        stopUseProgram() const { OpenGLFunction::functions().glUseProgram(0); }

    int                                         getUniformLocation(const std::string &name) const;
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

    void                                        bindTexture(int type, const std::string &name, GLuint id);
    void                                        unbindTexture();

private:
    GLuint                                      _programId;

    Shader                                      _vertShader;
    Shader                                      _geomShader;
    Shader                                      _fragShader;

    std::map<std::string, int>                  _uniformLocations;
    std::map<std::string, int>                  _attributeLocations;
};
