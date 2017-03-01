#include <iostream>
#include <nanogui/opengl.h>

#include "core/shader/shader.h"

Shader::Shader(ShaderType type, const std::string& path) :
    _handle(type),
    _path(path)
{}

unsigned int Shader::getId() const
{
    return _handle.getId();
}

const std::string& Shader::getPath() const
{
    return _path;
}

bool Shader::compile()
{
    return compile(_path);
}

bool Shader::compile(const std::string& path)
{
    _path = path;

    bool success = true;

    unsigned int id = _handle.getId();

    if (success = (id == 0))
    {
        std::cerr << "Shader id is not valid !" << std::endl;
    }
    else
    {
        std::string src = fileToString(_path);

        if (success = (src.length() != 0))
        {
            const char* shaderSource = src.c_str();

            glShaderSource(id, 1, &shaderSource, NULL);

            glCompileShader(id);

            printShaderInfo("Shader " + path + " compilation result: ");
        }
        else
        {
            std::cerr << "Unable to read shader source file" << path << std::endl;
        }
    }
    return success;
}

std::string Shader::fileToString(const std::string& filename)
{
    FILE *fp;
    char *content = nullptr;

    int count = 0;

    if (filename != std::string(""))
    {
        //fopen_s doesn't work on linux, let's keep good old fopen
        fp = fopen(filename.c_str(), "rt");

        if (fp != nullptr)
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

    std::string str(content);
    delete[] content;

    return str;
}

bool Shader::printShaderInfo(const std::string& msg)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetShaderiv(_handle.getId(), GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(_handle.getId(), infologLength, &charsWritten, infoLog);

        std::cerr << msg << " : " << infoLog << std::endl;
        free(infoLog);
    }

    return (infologLength == 1);
}
