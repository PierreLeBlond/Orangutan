/**
 * \file shader.cpp
 * \brief Sources de la classe de gestion d'un type de shader.
 * \author Pierre Lespingal
 * \version 1.0
 * \date 20 fevrier 2015
 *
 * Classe representant un type de shader, à utiliser dans un pipeline graphique via la classe ShaderProgram.
 *
 */

#include "shader.h"


Shader::Shader(GLenum type)
{
    _shaderId = OpenGLFunction::functions().glCreateShader(type);
    if(0==_shaderId)
    {
        std::cerr << "Error creating shader type " << type << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Create shader id : " << _shaderId << std::endl;
}


Shader::~Shader()
{
    OpenGLFunction::functions().glDeleteShader(_shaderId);
}

bool Shader::compileShader(std::string filename)
{
    //Test si l'id du shader est valide
    if (_shaderId == 0)
    {
        std::cerr << "Shader id is not valid !" << std::endl;
        return false;
    }

    //Charge le fichier source
    std::string src = readFileSrc(filename);

    if (src.length() == 0)
    {
        std::cerr << "Unable to read shader source file" << filename << std::endl;
        return false;
    }

    const char *shaderSource = src.c_str();

    OpenGLFunction::functions().glShaderSource(_shaderId, 1, &shaderSource, NULL);

    //Compilation du shader
    OpenGLFunction::functions().glCompileShader(_shaderId);
    printInfoLogShader("Shader " + filename + " compilation result: ");

    return true;
}

std::string Shader::readFileSrc(std::string filename)
{
    FILE *fp;
    char *content = NULL;

    int count = 0;

    if (filename != std::string(""))
    {
        fopen_s(&fp, filename.c_str(), "rt");

        if (fp != NULL)
        {

            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);

            if (count > 0)
            {
                content = new char[count + 1];
                count = (int) fread(content, sizeof(char), count, fp);
                content[count] = '\0';
            }

            fclose(fp);
        }
        else
        {
            std::cout << "Shader : cannot open " << filename << std::endl;
        }
    }

    return std::string(content);
}

bool Shader::printInfoLogShader(std::string msg)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    OpenGLFunction::functions().glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1)
    {
        infoLog = (char *)malloc(infologLength);
        OpenGLFunction::functions().glGetShaderInfoLog(_shaderId, infologLength, &charsWritten, infoLog);

        std::cerr << msg << " : " << infoLog << std::endl;
        free(infoLog);
    }

    return (infologLength == 1);
}
