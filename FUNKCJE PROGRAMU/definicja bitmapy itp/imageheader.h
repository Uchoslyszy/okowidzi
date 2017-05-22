#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H
#include"bitmap_image.hpp"

class Picture{
    private:
        bitmap_image image;
        int * histogram;
        unsigned int height;
        unsigned int width;

    public:
        int image_open(std::string name);
        bitmap_image grayscaling();
        int generate_histogram();
        void lightening(int scale);
        int image_save(std::string path);
        ~Picture();
};

void array_clean(int * array_h);

#endif // IMAGEHEADER_H
