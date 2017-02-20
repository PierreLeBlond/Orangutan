#include "core/shaderprogram.h"
#include "core/debug.h"

#include "core/qt/context.h"

ShaderProgram::ShaderProgram() : _programId(Context::functions().glCreateProgram()),
_vertShader(O_VERTEX), _geomShader(O_GEOMETRY), _fragShader(O_FRAGMENT)
{
}

ShaderProgram::~ShaderProgram()
{
    detachGeometryShader();
    detachFragmentShader();
    detachVertexShader();

    Context::functions().glDeleteProgram(_programId);
}

bool ShaderProgram::attachGeometryShader()
{
    Context::functions().glAttachShader(_programId, _geomShader.shaderId());
    return true;
}

bool ShaderProgram::attachVertexShader()
{
    Context::functions().glAttachShader(_programId, _vertShader.shaderId());
    return true;
}

bool ShaderProgram::attachFragmentShader()
{
    Context::functions().glAttachShader(_programId, _fragShader.shaderId());
    return true;
}

bool ShaderProgram::linkProgram()
{
    Context::functions().glLinkProgram(_programId);

    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    Context::functions().glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1)
    {
        infoLog = (char *)malloc(infologLength);
        Context::functions().glGetProgramInfoLog(_programId, infologLength, &charsWritten, infoLog);

        std::cerr << "Link message :" << infoLog;
        free(infoLog);
    }

    return (infologLength == 1);
}

bool ShaderProgram::detachFragmentShader()
{
    Context::functions().glDetachShader(_programId, _fragShader.shaderId());
    return true;
}

bool ShaderProgram::detachVertexShader()
{
    Context::functions().glDetachShader(_programId, _vertShader.shaderId());
    return true;
}

bool ShaderProgram::detachGeometryShader()
{
    Context::functions().glDetachShader(_programId, _geomShader.shaderId());
    return true;
}

void ShaderProgram::startUseProgram() const
{
    Context::functions().glUseProgram(_programId);
}

void ShaderProgram::stopUseProgram() const
{
    Context::functions().glUseProgram(_programId);
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
    Context::functions().glGetProgramInterfaceiv(_programId, GL_UNIFORM, GL_ACTIVE_RESOURCES, &nbOfUniforms);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

    for(int i = 0; i < nbOfUniforms;i++)
    {
        GLint results[4];
        Context::functions().glGetProgramResourceiv(_programId, GL_UNIFORM, i, 4, properties, 4, NULL, results);
        if(results[3] != -1)
        {

        }
        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        Context::functions().glGetProgramResourceName(_programId, GL_UNIFORM, i, nameBufSize, NULL, name);
        //std::cout << results[2] << " " << name << " " << results[1] << std::endl;
        _uniformLocations[std::string(name)] = results[2];
        delete [] name;
    }
}

void ShaderProgram::storeAttributeLocation()
{
    GLint nbOfAttributes = 0;
    Context::functions().glGetProgramInterfaceiv(_programId,
                                                        GL_PROGRAM_INPUT,
                                                        GL_ACTIVE_RESOURCES,
                                                        &nbOfAttributes);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

    for(int i = 0; i < nbOfAttributes;i++)
    {
        GLint results[3];
        Context::functions().glGetProgramResourceiv(_programId,
                                                           GL_PROGRAM_INPUT,
                                                           i, 4, properties, 3,
                                                           NULL, results);
        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        Context::functions().glGetProgramResourceName(_programId,
                                                             GL_PROGRAM_INPUT,
                                                             i, nameBufSize,
                                                             NULL, name);
        std::cout << results[2] << " " << name << " " << results[1] << std::endl;
        _attributeLocations[std::string(name)] = results[2];
        delete [] name;
    }
}

int ShaderProgram::getUniformLocation(const std::string &name) const
{
    auto it = _uniformLocations.find(name);
    if(it != _uniformLocations.end())
        return it->second;
    else
    {
        return -1;
    }
}

int ShaderProgram::getAttributeLocation(const std::string &name) const
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

void ShaderProgram::setUniform(const std::string &name, const glm::vec3 &v)
{
    Context::functions().glUniform3fv(_uniformLocations[name], 1,
                                             glm::value_ptr(v));
}

void ShaderProgram::setUniform(const std::string &name, const glm::vec4 &v)
{
    Context::functions().glUniform4fv(_uniformLocations[name], 1,
                                             glm::value_ptr(v));
}

void ShaderProgram::setUniform(const std::string &name, const glm::mat3 &m)
{
    Context::functions().glUniformMatrix3fv(_uniformLocations[name], 1,
                                                   GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const std::string &name, const glm::mat4 &m)
{
    Context::functions().glUniformMatrix4fv(_uniformLocations[name], 1,
                                                   GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const std::string &name, float val)
{
    Context::functions().glUniform1f(_uniformLocations[name], val);
}

void ShaderProgram::setUniform(const std::string &name, int val)
{
    Context::functions().glUniform1i(_uniformLocations[name], val);
}

void ShaderProgram::setUniform(const std::string &name, unsigned int val)
{
    Context::functions().glUniform1ui(_uniformLocations[name], val);
}

void ShaderProgram::setUniform(const std::string &name, bool val)
{
    Context::functions().glUniform1i(_uniformLocations[name], val);
}

void ShaderProgram::bindTexture(int type, const std::string &name, unsigned int id)
{
    if(type == O_TEXTURE_2D)
    {
        Context::functions().glUniform1i(_uniformLocations[name], 0);
        Context::functions().glActiveTexture(GL_TEXTURE0 + 0);
        Context::functions().glBindTexture(GL_TEXTURE_2D, id);
    }else if(type == O_TEXTURE_CUBE_MAP)
    {
        Context::functions().glUniform1i(_uniformLocations[name], 2);
        Context::functions().glActiveTexture(GL_TEXTURE0 + 2);
        Context::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    }
}

void ShaderProgram::unbindTexture()
{
    Context::functions().glBindTexture(GL_TEXTURE_2D, 0);
    Context::functions().glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}