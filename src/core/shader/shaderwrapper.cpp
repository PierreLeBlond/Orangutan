#include "core/shader/shaderwrapper.h"

#include <nanogui/opengl.h>

ShaderWrapper::ShaderWrapper(const std::string& name) :
    Asset(name)
{
}

void ShaderWrapper::build(const std::string& vertexShaderPath,
                          const std::string& fragmentShaderPath,
                          const std::string& geometryShaderPath)
{
    if (!_shaderProgram.build(vertexShaderPath, fragmentShaderPath, geometryShaderPath))
        std::cout << "Build aborted, go figure out why by yourself, I'm done dealing with bad coders." << std::endl;
    storeAttributeLocation();
    storeUniformLocation();
}

void ShaderWrapper::start() const
{
    _shaderProgram.start();
}

void ShaderWrapper::stop() const
{
    _shaderProgram.stop();
}

void ShaderWrapper::storeUniformLocation()
{
    GLint nbOfUniforms = 0;
    glGetProgramInterfaceiv(_shaderProgram.getId(), GL_UNIFORM, GL_ACTIVE_RESOURCES, &nbOfUniforms);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

    for(int i = 0; i < nbOfUniforms;i++)
    {
        GLint results[4];
        glGetProgramResourceiv(_shaderProgram.getId(), GL_UNIFORM, i, 4, properties, 4, NULL, results);
        if(results[3] != -1)
        {

        }
        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        glGetProgramResourceName(_shaderProgram.getId(), GL_UNIFORM, i, nameBufSize, NULL, name);
        //std::cout << results[2] << " " << name << " " << results[1] << std::endl;
        _uniformLocations[std::string(name)] = results[2];
        delete [] name;
    }
}

void ShaderWrapper::storeAttributeLocation()
{
    GLint nbOfAttributes = 0;
    glGetProgramInterfaceiv(_shaderProgram.getId(),
                            GL_PROGRAM_INPUT,
                            GL_ACTIVE_RESOURCES,
                            &nbOfAttributes);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

    for(int i = 0; i < nbOfAttributes;i++)
    {
        GLint results[3];
        glGetProgramResourceiv(_shaderProgram.getId(),
                               GL_PROGRAM_INPUT,
                               i, 4, properties, 3,
                               NULL, results);
        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        glGetProgramResourceName(_shaderProgram.getId(),
                                 GL_PROGRAM_INPUT,
                                 i, nameBufSize,
                                 NULL, name);
        std::cout << results[2] << " " << name << " " << results[1] << std::endl;
        _attributeLocations[std::string(name)] = results[2];
        delete [] name;
    }
}

int ShaderWrapper::getUniformLocation(const std::string &name) const
{
    auto it = _uniformLocations.find(name);
    if(it != _uniformLocations.end())
        return it->second;
    else
    {
        return -1;
    }
}

std::vector<std::string> ShaderWrapper::getUniformsName() const
{
    std::vector<std::string> names;
    for(auto const& p : _uniformLocations)
    {
        names.push_back(p.first);
    }
    return names;
}

int ShaderWrapper::getAttributeLocation(const std::string &name) const
{
    auto it = _attributeLocations.find(name);
    if(it != _attributeLocations.end())
        return it->second;
    else
    {
        std::cout << "Error : could not find attribute location of : " << name << std::endl;
        return -1;
    }
}

void ShaderWrapper::setUniform(const std::string &name, const glm::vec3 &v)
{
    glUniform3fv(_uniformLocations[name], 1, glm::value_ptr(v));
}

void ShaderWrapper::setUniform(const std::string &name, const glm::vec4 &v)
{
    glUniform4fv(_uniformLocations[name], 1, glm::value_ptr(v));
}

void ShaderWrapper::setUniform(const std::string &name, const glm::mat3 &m)
{
    glUniformMatrix3fv(_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderWrapper::setUniform(const std::string &name, const glm::mat4 &m)
{
    glUniformMatrix4fv(_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderWrapper::setUniform(const std::string &name, float val)
{
    glUniform1f(_uniformLocations[name], val);
}

void ShaderWrapper::setUniform(const std::string &name, int val)
{
    glUniform1i(_uniformLocations[name], val);
}

void ShaderWrapper::setUniform(const std::string &name, unsigned int val)
{
    glUniform1ui(_uniformLocations[name], val);
}

void ShaderWrapper::setUniform(const std::string &name, bool val)
{
    glUniform1i(_uniformLocations[name], val);
}

void ShaderWrapper::bindTexture(const std::string &name, unsigned int id)
{
    glUniform1i(_uniformLocations[name], 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, id);
}

void ShaderWrapper::bindCubeTexture(const std::string &name, unsigned int id)
{
    glUniform1i(_uniformLocations[name], 2);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void ShaderWrapper::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

unsigned int ShaderWrapper::getProgramId() const
{
    return _shaderProgram.getId();
}
