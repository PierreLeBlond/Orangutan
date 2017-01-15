#include "util/image.h"

#include <iostream>

void* Image::loadPNG(const char* filename, int* width, int* height)
{
    unsigned char header[8];
    FILE* fp = fopen(filename, "rb");
    if(!fp)
        std::cout << "Couldn't open the file : " << filename << std::endl;
    else
    {
        fread(header, 1, 8, fp);
        bool is_png = !png_sig_cmp(header, 0, 8);
        if(!is_png)
            std::cout << "Not png : " << filename << std::endl;
        else
        {
            /* initialize stuff */
            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

            if (!png_ptr)
            {
                std::cout << "png_create_read_struct failed !" << std::endl;
                return NULL;
            }

            png_infop info_ptr = png_create_info_struct(png_ptr);
            if (!info_ptr)
            {
                std::cout << "png_create_info_struct failed !" << std::endl;
                return NULL;
            }

            if (setjmp(png_jmpbuf(png_ptr)))
            {
                std::cout << "Error during init_io" << std::endl;
                return NULL;
            }

            png_init_io(png_ptr, fp);
            png_set_sig_bytes(png_ptr, 8);

            png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

            png_uint_32 w, h;
            int bit_depth;
            int color_type, interlace_type;
            png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type,
                         &interlace_type, NULL, NULL);
            *width = w;
            *height = h;
            if(color_type != PNG_COLOR_TYPE_RGBA)
                std::cout << "Color type must be RGBA" << std::endl;

            unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
            unsigned char *data = (unsigned char*) malloc(row_bytes * *height);

            png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

            for (int i = 0; i < *height; i++) {
                // note that png is ordered top to
                // bottom, but OpenGL expect it bottom to top
                // so the order or swapped
                std::memcpy(data+(row_bytes * (*height-1-i)), row_pointers[i], row_bytes);
            }

            /* Clean up after the read,
             * and free any memory allocated */
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

            fclose(fp);

            return data;
        }
    }
    return NULL;
}
