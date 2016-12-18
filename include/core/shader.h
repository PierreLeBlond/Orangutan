#pragma once
#include <GL/gl.h>

#include <string>
#include <iostream>

/**
 * @class Shader
 */
class Shader
{
public:
    /**
     * @brief Shader
     * @param type : Le type de shader souhaité
     * @param funcs : Un pointeur vers les fonctions OpenGl 3.3
     *
     * Constructeur de la classe Shader
     */
    Shader(GLenum type);

    /**
     * @brief ~Shader
     *
     * Destructeur de la classe Shader
     */
    ~Shader();

    /**
     * @brief compileShader
     * @param filename : Le nom du fichier à compiler.
     * @return Un boolean indiquant si la compilation à réussie.
     *
     * Compile le shader contenu dans le fichier filename.
     */
    bool compileShader(std::string filename);


    /**
     * @brief shaderId
     * @return L'id du shader
     *
     * Assesseur de l'attribut _shaderId.
     */
    GLuint shaderId() const			{ return _shaderId; }

private:
    GLuint _shaderId;/**< L'id du shader*/

    /**
     * @brief readFileSrc
     * @param filename : Le fichier source du shader.
     * @return : Le contenu du fichier shader.
     *
     * Lit le contenu du fichier.
     */
    std::string readFileSrc(std::string filename);

    /**
     * @brief printInfoLogShader
     * @param msg
     * @return : Un booléan indiquant la réussite de la compilation.
     *
     * Log de la compialtion du shader.
     */
    bool printInfoLogShader(std::string msg);
};
