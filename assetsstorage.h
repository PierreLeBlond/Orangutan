#ifndef ASSETSSTORAGE_H
#define ASSETSSTORAGE_H

#include <vector>

#include "mesh.h"
#include "texture.h"
#include "Shader/shaderstrategy.h"


class AssetsStorage
{
public:
                                                            AssetsStorage();
                                                            ~AssetsStorage();

    const std::vector<const Mesh>&                          getMeshs() const;
    const std::vector<GLuint>&                              getTextures() const;
    const std::vector<const ShaderProgram*>&                getShaderPrograms() const;
    const std::vector<const ShaderStrategy*>&               getShaderStrategies() const;

    int                                                     getNumberOfMeshs() const;
    int                                                     getNumberOfTextures() const;
    int                                                     getNumberOfShaderPrograms() const;
    int                                                     getNumberOfShaderStrategies() const;

    const Mesh&                                             getMesh(int index) const;
    GLuint                                                  getTexture(int index) const;
    const ShaderProgram&                                    getShaderProgram(int index) const;
    const ShaderStrategy*                                   getShaderStrategy(int index) const;

    void                                                    addMesh(const Mesh mesh);
    void                                                    addTexture(GLuint texture);
    void                                                    addShaderProgram(const ShaderProgram *shaderProgram);
    void                                                    addShaderStrategy(const ShaderStrategy *shaderStrategy);

private:
    std::vector<const Mesh>                                 _meshs;
    std::vector<GLuint>                                     _textures;
    std::vector<const ShaderProgram*>                        _shaderPrograms;
    std::vector<const ShaderStrategy*>                      _shaderStrategies;
};

#endif // ASSETSSTORAGE_H
