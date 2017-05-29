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
        Picture(const QString path);
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
        void medianFilter(int mask_size);//color values of pixel are median values of pixels nerby
        void pixelizeFilter(int mask_size);//makes pixels on the image larger mask size determines new pixel size
        int gaussianBlur(int mask_size,double sigma);//(mask size determines size of filter's matrix, number of pixels that influence, sigma defines gauss curve width)
        int equalFilter(int mask_size); //(filter using matrix filled with ones, all pixels have equal influence on the output color)


        void lightening(int scale);//brightness gets scale value added not multiplied
        void imageCopy(int width, int height, Picture image);//(copies image with its width and height into this)
        int imageOpen(const QString name);//name-path for file to open \ errors:(-1 = cannot open file)
        int imageSave(const QString path);//path-path for file to save in

};

void arraySort(double * array,int size);
void array_clean(int * array_h);
int generateGaussian(double ** array,int scale,double sigma);

#endif // IMAGEHEADER_H
