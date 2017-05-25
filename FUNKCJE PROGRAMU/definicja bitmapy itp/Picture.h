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

        void grayscaling();
        void generateHistogram();
        void printHistogram();
        int imagefilter(int filter_number,int mask_size); //filter number picks up filter 1-Gaussian Blur

        void lightening(int scale);//brightness gets scale value added not multiplied
        void imageCopy(int width, int height, Picture image, Picture new_image);
        int imageOpen(const QString name);//name-path for file to open \ errors:(-1 = cannot open file)
        int imageSave(const QString path);//path-path for file to save in

};

void array_clean(int * array_h);
void generateGaussian(double ** array,int scale);

#endif // IMAGEHEADER_H
