#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <QImage>

#include "core/opengl.h"
#include "object/asset.h"

enum Image_type {
    O_TEXTURE_2D = GL_TEXTURE_2D,
    O_TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP
};

class Texture : public Asset
{
public:
                                Texture(std::string path, std::string name = "unknow");
                                Texture();

    GLuint                      getId() const;

    void                        load(std::string path);

    void                        loadCubeMap(std::string path_prefix);

private:
    GLuint                      _id;
    std::string                 _path;
    int                         _type;
    QImage                      _image;
};

#endif // TEXTURE_H
