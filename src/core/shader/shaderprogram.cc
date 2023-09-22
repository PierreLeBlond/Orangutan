#include "core/shader/shaderprogram.h"

#include <nanogui/opengl.h>

#include <iostream>

namespace orangutan {

ShaderProgram::ShaderProgram()
    : vertex_shader_(ShaderType::VERTEX),
      fragment_shader_(ShaderType::FRAGMENT),
      geometry_shader_(ShaderType::GEOMETRY) {}

bool ShaderProgram::Attach(unsigned int id) {
  int numberOfAttachedShader = 0;
  glGetProgramiv(handle_.getId(), GL_ATTACHED_SHADERS, &numberOfAttachedShader);

  if (numberOfAttachedShader >= MAX_ATTACHED_SHADER) {
    return false;
  }

  glAttachShader(handle_.getId(), id);

  return true;
}

bool ShaderProgram::Link() {
  glLinkProgram(handle_.getId());

  int infologLength = 0;
  int charsWritten = 0;
  char* infoLog;

  glGetProgramiv(handle_.getId(), GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 1) {
    infoLog = (char*)malloc(infologLength);
    glGetProgramInfoLog(handle_.getId(), infologLength, &charsWritten, infoLog);

    std::cerr << "Link message :" << infoLog;
    free(infoLog);
  }

  return (infologLength == 1);
}

bool ShaderProgram::Detach(unsigned int id) {
  glDetachShader(handle_.getId(), id);
  return true;
}

bool ShaderProgram::Build(const std::vector<std::string>& defines) {
  return Build(defines, vertex_shader_.GetPath(), fragment_shader_.GetPath(),
               geometry_shader_.GetPath());
}

bool ShaderProgram::Build(const std::vector<std::string>& defines,
                          const std::string& vertex_shader_path,
                          const std::string& fragment_shader_path,
                          const std::string& geometry_shader_path) {
  // Check if shader are already attached, and if so detach them first
  int numberOfAttachedShader = 0;
  unsigned int shaders[MAX_ATTACHED_SHADER];
  glGetAttachedShaders(handle_.getId(), MAX_ATTACHED_SHADER,
                       &numberOfAttachedShader, shaders);
  for (int i = 0; i < numberOfAttachedShader; ++i) {
    Detach(shaders[i]);
  }

  bool hasCompiled = vertex_shader_.Compile(defines, vertex_shader_path) &&
                     fragment_shader_.Compile(defines, fragment_shader_path);

  if (!hasCompiled) {
    return false;
  }

  Attach(vertex_shader_.GetId());
  Attach(fragment_shader_.GetId());

  if (geometry_shader_path != "") {
    bool geometryShaderHasCompiled =
        geometry_shader_.Compile(defines, geometry_shader_path) &&
        Attach(geometry_shader_.GetId());
    if (!geometryShaderHasCompiled) {
      return false;
    }
  }

  Link();

  return true;
}

void ShaderProgram::Start() const { glUseProgram(handle_.getId()); }

void ShaderProgram::Stop() const { glUseProgram(0); }

unsigned int ShaderProgram::GetId() const { return handle_.getId(); }

}  // namespace orangutan
