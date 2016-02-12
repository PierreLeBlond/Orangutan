#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <QImage>
#include "opengl.h"

class Texture
{
public:
                                Texture(std::string path);
                                Texture();

    GLuint                      getId() const;

    void                        setId(GLuint id);

    void                        load(std::string path);

private:
    GLuint                      _id;
    std::string                 _path;
    QImage                      _image;
};

#endif // TEXTURE_H
