#include "core/shader/shaderprogram.h"

#include <nanogui/opengl.h>

#include <iostream>

namespace orangutan {

ShaderProgram::ShaderProgram()
    : _vertexShader(ShaderType::VERTEX),
      _fragmentShader(ShaderType::FRAGMENT),
      _geometryShader(ShaderType::GEOMETRY) {}

bool ShaderProgram::attach(unsigned int id) {
  int numberOfAttachedShader = 0;
  glGetProgramiv(_handle.getId(), GL_ATTACHED_SHADERS, &numberOfAttachedShader);

  if (numberOfAttachedShader >= MAX_ATTACHED_SHADER) {
    return false;
  }

  glAttachShader(_handle.getId(), id);

  return true;
}

bool ShaderProgram::link() {
  glLinkProgram(_handle.getId());

  int infologLength = 0;
  int charsWritten = 0;
  char* infoLog;

  glGetProgramiv(_handle.getId(), GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 1) {
    infoLog = (char*)malloc(infologLength);
    glGetProgramInfoLog(_handle.getId(), infologLength, &charsWritten, infoLog);

    std::cerr << "Link message :" << infoLog;
    free(infoLog);
  }

  return (infologLength == 1);
}

bool ShaderProgram::detach(unsigned int id) {
  glDetachShader(_handle.getId(), id);
  return true;
}

bool ShaderProgram::build() {
  return build(_vertexShader.getPath(), _fragmentShader.getPath(),
               _geometryShader.getPath());
}

bool ShaderProgram::build(const std::string& vertexShaderPath,
                          const std::string& fragmentShaderPath,
                          const std::string& geometryShaderPath) {
  // Check if shader are already attached, and if so detach them first
  int numberOfAttachedShader = 0;
  unsigned int shaders[MAX_ATTACHED_SHADER];
  glGetAttachedShaders(_handle.getId(), MAX_ATTACHED_SHADER,
                       &numberOfAttachedShader, shaders);
  for (int i = 0; i < numberOfAttachedShader; ++i) detach(shaders[i]);

  bool hasCompiled = _vertexShader.compile(vertexShaderPath) &&
                     _fragmentShader.compile(fragmentShaderPath);

  if (!hasCompiled) {
    return false;
  }

  attach(_vertexShader.getId());
  attach(_fragmentShader.getId());

  if (geometryShaderPath != "") {
    bool geometryShaderHasCompiled =
        _geometryShader.compile(geometryShaderPath) &&
        attach(_geometryShader.getId());
    if (!geometryShaderHasCompiled) {
      return false;
    }
  }

  link();

  return true;
}

void ShaderProgram::start() const { glUseProgram(_handle.getId()); }

void ShaderProgram::stop() const { glUseProgram(0); }

unsigned int ShaderProgram::getId() const { return _handle.getId(); }

}  // namespace orangutan
