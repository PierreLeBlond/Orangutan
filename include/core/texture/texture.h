#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>

#include "core/texture/texturehandle.h"
#include "object/asset.h"

class Texture : public Asset
{
public:
                                Texture(const std::string &name = "Texture X");
                                Texture(const std::string &path, const std::string &name);

    unsigned int                getId() const;
    const std::string&          getPath() const;

    virtual bool                load(const std::string &path) = 0;

protected:
    TextureHandle               _handle;
    std::string                 _path;
};

#endif // TEXTURE_H
