#ifndef DDTEXTURE_H
#define DDTEXTURE_H

#include "core/texture/texture.h"

class DDTexture : public Texture
{
public:
                                DDTexture(const std::string &name = "2DTexture X");
                                DDTexture(const std::string &path,
                                          const std::string &name);

    virtual bool                load(const std::string &path);
};

#endif // DDTEXTURE_H
