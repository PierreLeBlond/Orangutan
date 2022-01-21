#ifndef IMAGE_H
#define IMAGE_H

#include <locale.h>
#include <png.h>

#include <cstring>
#include <memory>
#include <sstream>
#include <vector>

class Image {
 public:
  static unsigned char* loadPNG(const char* filename, int* width, int* height);
};

#endif  // IMAGE_H
