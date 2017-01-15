#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <cstring>
#include <memory>
#include <sstream>
#include <locale.h>

#include <png.h>

class Image
{
public:
    static void*                        loadPNG(const char* filename, int* width, int* height);
};

#endif // IMAGE_H
