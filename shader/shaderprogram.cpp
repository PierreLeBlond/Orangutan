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

#include "shaderprogram.h"


ShaderProgram::ShaderProgram() : _programId(OpenGLFunction::functions().glCreateProgram()), _vertShader(GL_VERTEX_SHADER), _fragShader(GL_FRAGMENT_SHADER), _geomShader(GL_GEOMETRY_SHADER)
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

    return true;
}
