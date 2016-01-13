/**
 * \file shaderprogram.h
 * \brief Header de la classe d'assemblage de shader dans un programme.
 * \author Pierre Lespingal
 * \version 1.0
 * \date 20 fevrier 2015
 *
 * Classe regroupant plusieurs shader, pour construire un pipeline graphique.
 *
 */

#pragma once

#include "shader.h"
#include "../material.h"
#include "../lightnode.h"
#include "../mesh.h"
#include "../util.h"

#include "../opengl.h"

#include <sstream>

#define MAX_LIGHT 8

/**
 * @class ShaderProgram
 * @brief Cette classe regroupe et associe les shaders constituant le pipeline graphique
 */
class ShaderProgram
{
public:
                                                ShaderProgram();
                                                ~ShaderProgram();

    inline GLuint                               getProgramId()      const { return _programId; }
    inline const Shader&                        getVertexShader()   const { return _vertShader; }
    inline const Shader&                        getGeometryShader() const { return _geomShader; }
    inline const Shader&                        getFragmentShader() const { return _fragShader; }

    bool                                        initShader(const std::string &vert_location, const std::string &frag_location, const std::string &geom_location = "");

    bool                                        attachGeometryShader();
    bool                                        attachVertexShader();
    bool                                        attachFragmentShader();
    bool                                        linkProgram();
    bool                                        detachFragmentShader();
    bool                                        detachVertexShader();
    bool                                        detachGeometryShader();

    inline void                                 startUseProgram() const { OpenGLFunction::functions().glUseProgram(_programId); }
    inline void                                 stopUseProgram() const { OpenGLFunction::functions().glUseProgram(0); }

private:
    GLuint                                      _programId;

    Shader                                      _vertShader;
    Shader                                      _geomShader;
    Shader                                      _fragShader;
};

