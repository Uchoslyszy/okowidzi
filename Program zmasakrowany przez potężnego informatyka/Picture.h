#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H
#include<QImage>

class Picture{
    private:
        struct histogram
        {
            int * red;
            int * blue;
            int * green;
        };

        histogram histogram;
        QImage image;
        unsigned int height;
        unsigned int width;

    public:
        Picture(const QString name);
        Picture(int width,int height,QImage::Format format);
        Picture();
        ~Picture();

        int Width();
        int Height();
        QImage::Format format();
        QImage imagePointer();

        void grayscaling();
        void generateHistogram();
        void printHistogram();
        void contrast (int set);
        void medianFilter(int mask_size);
        void pixelizeFilter(int mask_size);
        int gaussianBlur(int mask_size,double sigma);
        int equalFilter(int mask_size); //(filter number, size of the mask(has to be an odd number),sigma value(for gaussian blur))
        /*filters:
                1. Gaussian blur
                2. Equal blur
                3. Pixelize(mask size chooses new pixel size)
        */

        void lightening(int scale);//brightness gets scale value added not multiplied
        void imageCopy(int width, int height, Picture* image);
        int imageOpen(const QString name);//name-path for file to open \ errors:(-1 = cannot open file)
        int imageSave(const QString path);//path-path for file to save in

};

void arraySort(double * array,int size);
void array_clean(int * array_h);
int generateGaussian(double ** array,int scale,double sigma);

#endif // IMAGEHEADER_H
