#include "core/shader/shader.h"

#include <nanogui/opengl.h>

#include <iostream>
#include <sstream>

namespace orangutan {

Shader::Shader(ShaderType type, const std::string& path)
    : handle_(type), path_(path) {}

unsigned int Shader::GetId() const { return handle_.getId(); }

const std::string& Shader::GetPath() const { return path_; }

bool Shader::Compile(const std::vector<std::string>& defines) {
  return Compile(defines, path_);
}

bool Shader::Compile(const std::vector<std::string>& defines,
                     const std::string& path) {
  path_ = path;

  unsigned int id = handle_.getId();

  if (id == 0) {
    std::cerr << "Shader id is not valid !" << std::endl;
    return false;
  }

  std::string src = FileToString(path_);

  if (src.length() == 0) {
    std::cerr << "Unable to read shader source file" << path << std::endl;
    return false;
  }

  std::ostringstream ost;
  ost << "#version 450 core\n";
  for (const std::string& define : defines) {
    ost << "#define " << define << "\n";
  }

  ost << src;

  std::string final_str = ost.str();

  const char* shaderSource = final_str.c_str();

  glShaderSource(id, 1, &shaderSource, nullptr);

  glCompileShader(id);

  PrintShaderInfo("Shader " + path + " compilation result: ");

  return true;
}

std::string Shader::FileToString(const std::string& filename) {
  FILE* fp;
  char* content = nullptr;

  int count = 0;

  if (filename != std::string("")) {
    // fopen_s doesn't work on linux, let's keep good old fopen
    fp = fopen(filename.c_str(), "rt");

    if (fp != nullptr) {
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

      if (count > 0) {
        content = new char[count + 1];
        count = (int)fread(content, sizeof(char), count, fp);
        content[count] = '\0';
      }

      fclose(fp);
    } else {
      std::cerr << "Shader : cannot open " << filename << std::endl;
    }
  }

  std::string str(content);
  delete[] content;

  return str;
}

bool Shader::PrintShaderInfo(const std::string& msg) {
  int infologLength = 0;
  int charsWritten = 0;
  char* infoLog;

  glGetShaderiv(handle_.getId(), GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 1) {
    infoLog = (char*)malloc(infologLength);
    glGetShaderInfoLog(handle_.getId(), infologLength, &charsWritten, infoLog);

    std::cerr << msg << " : " << infoLog << std::endl;
    free(infoLog);
  }

  return (infologLength == 1);
}

}  // namespace orangutan
