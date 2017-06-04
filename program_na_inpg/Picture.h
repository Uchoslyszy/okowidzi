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
        unsigned int imageHeight;
        unsigned int imageWidth;

    public:
        Picture(const QString path);
        Picture(int imageWidth,int imageHeight,QImage::Format format);
        Picture();
        ~Picture();

        int getWidth();
        int getHeight();
        QImage::Format format();
        QImage imagePointer();

        void grayscaling();
        void generateHistogram();
        void printHistogram();
        void contrast (int set,int scale);
        void medianFilter(int mask_size);
        void pixelizeFilter(int mask_size);
        int gaussianBlur(int mask_size,double sigma);
        int equalFilter(int mask_size); //size of the mask(should be an odd number)


        void lightening(int scale);//brightness gets scale value added not multiplied
        void imageCopy(int imageWidth, int imageHeight,QImage image);
        int imageOpen(const QString name);//name-path for file to open \ errors:(-1 = cannot open file)
        int imageSave(const QString path);//path-path for file to save in

};

void arraySort(double * array,int size);
void array_clean(int * array_h);
int generateGaussian(double ** array,int scale,double sigma);

#endif // IMAGEHEADER_H
