#ifndef OPENGLES_PICOPNG_H
#define OPENGLES_PICOPNG_H

#include "global.h"

class PicoPNG {
public:
    static int decodePNG(std::vector<unsigned char>& out_image,
                           unsigned long& image_width, unsigned long& image_height,
                           const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);
};

#endif // OPENGLES_PICOPNG_H
