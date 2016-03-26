#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <QImage>
#include "opengl.h"

class Texture
{
public:
                                Texture(std::string path, std::string name = "unknow");
                                Texture();

    GLuint                      getId() const;
    std::string                 getName() const;

    void                        setName(std::string name);

    void                        load(std::string path);

    void                        loadCubeMap(std::string path_prefix);

private:
    std::string                 _name;

    GLuint                      _id;
    std::string                 _path;
    QImage                      _image;
};

#endif // TEXTURE_H
