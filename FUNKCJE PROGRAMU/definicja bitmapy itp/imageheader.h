#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H
#include"bitmap_image.hpp"

class Picture{
    private:
        struct histogram
        {
            int * red;
            int * blue;
            int * green;
        };

        histogram histogram;
        bitmap_image image;
        unsigned int height;
        unsigned int width;

    public:
        int image_open(std::string name);
        int grayscaling();
        int generate_histogram();
        void lightening(int scale);
        int image_save(std::string path);
        ~Picture();
};

void array_clean(int * array_h);

#endif // IMAGEHEADER_H
