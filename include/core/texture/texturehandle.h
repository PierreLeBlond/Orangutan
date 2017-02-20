#ifndef TEXTURE_HANDLE_H
#define TEXTURE_HANDLE_H

#include "core/handle.h"

class TextureHandle : public Handle
{
  public:
                                TextureHandle();
                                TextureHandle(const TextureHandle& handle) = delete;
                                TextureHandle(TextureHandle&& handle) noexcept;

                                ~TextureHandle() noexcept;

    TextureHandle&              operator=(const TextureHandle& handle) = delete;
    TextureHandle&              operator=(TextureHandle&& handle);
};

#endif // TEXTURE_HANDLE_H
