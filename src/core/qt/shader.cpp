#include "core/shader.h"
#include "core/qt/context.h"

std::string Shader::readFileSrc(std::string filename)
{
    FILE *fp;
    char *content = NULL;

    int count = 0;

    if (filename != std::string(""))
    {
        //fopen_s doesn't work on linux, let's keep good old fopen
        fp = fopen(filename.c_str(), "rt");

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

Shader::Shader(unsigned int type)
{
    GLenum t;
    switch(type)
    {
      case O_VERTEX:
        t = GL_VERTEX_SHADER;
        break;
      case O_FRAGMENT:
        t = GL_FRAGMENT_SHADER;
        break;
      case O_GEOMETRY:
        t = GL_GEOMETRY_SHADER;
        break;
      default:
        t = GL_VERTEX_SHADER;
        break;
    }

    _shaderId = Context::functions().glCreateShader(t);
    if(0==_shaderId)
    {
        std::cout << "Error creating shader type " << type << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "Create shader id : " << _shaderId << std::endl;
}

Shader::~Shader()
{
    Context::functions().glDeleteShader(_shaderId);
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

    Context::functions().glShaderSource(_shaderId, 1, &shaderSource, NULL);

    //Compilation du shader
    Context::functions().glCompileShader(_shaderId);
    printInfoLogShader("Shader " + filename + " compilation result: ");

    return true;
}

bool Shader::printInfoLogShader(std::string msg)
{
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    Context::functions().glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1)
    {
        infoLog = (char *)malloc(infologLength);
        Context::functions().glGetShaderInfoLog(_shaderId, infologLength, &charsWritten, infoLog);

        std::cerr << msg << " : " << infoLog << std::endl;
        free(infoLog);
    }

    return (infologLength == 1);
}
