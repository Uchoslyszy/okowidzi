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
        int filter(int filter_number,int mask_size); //filter number picks up filter 1-Gaussian Blur
        int image_open(std::string name);//name-path for file to open \ errors:(-1 = cannot open file)

        int grayscaling();
        int generate_histogram();
        void lightening(int scale);//brightness gets scale value added not multiplied
        int image_save(std::string path);//path-path for file to save in
        ~Picture();
};

void array_clean(int * array_h);

#endif // IMAGEHEADER_H
