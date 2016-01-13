#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <QImage>
#include "opengl.h"

class Texture
{
public:
                                Texture();

    unsigned int                getNbTextures() const;

    std::vector<GLuint>         getIdTextures() const;

    void                        addTexture(GLuint id);
    void                        setTexture(GLuint id, int index);

    static GLuint               createTexture(QImage image);

private:
    unsigned int                _nbTextures;
    std::vector<GLuint>         _idTextures;
};

#endif // TEXTURE_H
