/**
 * \file shaderprogram.cpp
 * \brief Sources de la classe d'assemblage de shader dans un programme.
 * \author Pierre Lespingal
 * \version 1.0
 * \date 20 fevrier 2015
 *
 * Classe regroupant plusieurs shader, pour construire un pipeline graphique.
 *
 */

#include "core/shaderprogram.h"


ShaderProgram::ShaderProgram() : _programId(OpenGLFunction::functions().glCreateProgram()),
_vertShader(GL_VERTEX_SHADER), _geomShader(GL_GEOMETRY_SHADER), _fragShader(GL_FRAGMENT_SHADER)
{
}

ShaderProgram::~ShaderProgram()
{
    detachGeometryShader();
    detachFragmentShader();
    detachVertexShader();

    OpenGLFunction::functions().glDeleteProgram(_programId);
}

bool ShaderProgram::attachGeometryShader()
{
    OpenGLFunction::functions().glAttachShader(_programId, _geomShader.shaderId());
    return true;
}

bool ShaderProgram::attachVertexShader()
{
    OpenGLFunction::functions().glAttachShader(_programId, _vertShader.shaderId());
    return true;
}

bool ShaderProgram::attachFragmentShader()
{
    OpenGLFunction::functions().glAttachShader(_programId, _fragShader.shaderId());
    return true;
}

bool ShaderProgram::linkProgram()
{
    OpenGLFunction::functions().glLinkProgram(_programId);

    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    OpenGLFunction::functions().glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1)
    {
        infoLog = (char *)malloc(infologLength);
        OpenGLFunction::functions().glGetProgramInfoLog(_programId, infologLength, &charsWritten, infoLog);

        std::cerr << "Link message :" << infoLog;
        free(infoLog);
    }

    return (infologLength == 1);
}

bool ShaderProgram::detachFragmentShader()
{
    OpenGLFunction::functions().glDetachShader(_programId, _fragShader.shaderId());
    return true;
}

bool ShaderProgram::detachVertexShader()
{
    OpenGLFunction::functions().glDetachShader(_programId, _vertShader.shaderId());
    return true;
}

bool ShaderProgram::detachGeometryShader()
{
    OpenGLFunction::functions().glDetachShader(_programId, _geomShader.shaderId());
    return true;
}

bool ShaderProgram::initShader(const std::string& vert_location, const std::string& frag_location, const std::string& geom_location)
{
    if (!_vertShader.compileShader(vert_location)) {
        return false;
    }

    if (!_fragShader.compileShader(frag_location)) {
        return false;
    }

    //Attachement des shaders au programme
    attachVertexShader();
    attachFragmentShader();

    if(geom_location != ""){
        if (!_geomShader.compileShader(geom_location)) {
            return false;
        }
        attachGeometryShader();
    }
    linkProgram();
    storeUniformLocation();
    storeAttributeLocation();

    return true;
}

void ShaderProgram::storeUniformLocation()
{
    GLint nbOfUniforms = 0;
    OpenGLFunction::functions().glGetProgramInterfaceiv(_programId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &nbOfUniforms);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

    for(int i = 0; i < nbOfUniforms;i++)
    {
        GLint results[4];
        OpenGLFunction::functions().glGetProgramResourceiv(_programId, GL_UNIFORM, i, 4, properties, 4, NULL, results);
        if(results[3] != -1)
        {

        }
        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        OpenGLFunction::functions().glGetProgramResourceName(_programId, GL_UNIFORM, i, nameBufSize, NULL, name);
        std::cout << results[2] << " " << name << " " << results[1] << std::endl;
        _uniformLocations[std::string(name)] = results[2];
        delete [] name;
    }
}

void ShaderProgram::storeAttributeLocation()
{
    GLint nbOfAttributes = 0;
    OpenGLFunction::functions().glGetProgramInterfaceiv(_programId, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &nbOfAttributes);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

    for(int i = 0; i < nbOfAttributes;i++)
    {
        GLint results[3];
        OpenGLFunction::functions().glGetProgramResourceiv(_programId, GL_PROGRAM_INPUT, i, 4, properties, 3, NULL, results);
        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        OpenGLFunction::functions().glGetProgramResourceName(_programId, GL_PROGRAM_INPUT, i, nameBufSize, NULL, name);
        std::cout << results[2] << " " << name << " " << results[1] << std::endl;
        _attributeLocations[std::string(name)] = results[2];
        delete [] name;
    }
}

int ShaderProgram::getUniformLocation(const std::string &name) const
{
    return _uniformLocations.at(name);
}

int ShaderProgram::getAttributeLocation(const std::string &name) const
{
    return _attributeLocations.at(name);
}

void ShaderProgram::setUniform(const std::string &name, const glm::vec3 &v)
{
    OpenGLFunction::functions().glUniform3fv(_uniformLocations[name], 1, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const std::string &name, const glm::vec4 &v)
{
    OpenGLFunction::functions().glUniform4fv(_uniformLocations[name], 1, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const std::string &name, const glm::mat3 &m)
{
    OpenGLFunction::functions().glUniformMatrix3fv(_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const std::string &name, const glm::mat4 &m)
{
    OpenGLFunction::functions().glUniformMatrix4fv(_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const std::string &name, float val)
{
    OpenGLFunction::functions().glUniform1f(_uniformLocations[name], val);
}

void ShaderProgram::setUniform(const std::string &name, int val)
{
    OpenGLFunction::functions().glUniform1i(_uniformLocations[name], val);
}

void ShaderProgram::setUniform(const std::string &name, unsigned int val)
{
    OpenGLFunction::functions().glUniform1ui(_uniformLocations[name], val);
}

void ShaderProgram::setUniform(const std::string &name, bool val)
{
    OpenGLFunction::functions().glUniform1i(_uniformLocations[name], val);
}

void ShaderProgram::bindTexture(int type, const std::string &name, GLuint id)
{
    OpenGLFunction::functions().glUniform1i(_uniformLocations[name], GL_TEXTURE0);
    OpenGLFunction::functions().glActiveTexture(GL_TEXTURE0);
    OpenGLFunction::functions().glBindTexture(type, id);
}

void ShaderProgram::unbindTexture()
{
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_2D, 0);
    OpenGLFunction::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
