#include<iostream>
#include<stdlib.h>
#include "Picture.h"
#include<math.h>
#include<QImage>
#include<QRgb>
#include<QString>


Picture::Picture(const QString name)
{
    image.load(name);
    height=image.height();
    width=image.width();
}

Picture::Picture()
{

}

Picture::Picture(int width,int height,QImage::Format format)
{
    QImage image(width,height,format);
    height=image.height();
    width=image.width();
}


Picture::~Picture()
{
    if(histogram.red!=NULL)
        delete(histogram.red);
    if(histogram.blue!=NULL)
        delete(histogram.red);
    if(histogram.green!=NULL)
        delete(histogram.red);

}

/*int Picture::imagefilter(int filter_number,int mask_size)
{
    int r = floor(mask_size/2);
    int weight;
    int i,x,y,j,blue,red,green;

    rgb_t color;

    QImage image2(width,height);
    image2.copy_from(image);

    double ** mask;
    mask = new double*[mask_size];
    for(i=0;i<mask_size;i++)
        mask[i] = new double[mask_size];

    if(filter_number==1)
    {
        /*
        mask[0][0]=1;
        mask[0][1]=2;
        mask[0][2]=1;
        mask[1][0]=2;
        mask[1][1]=4;
        mask[1][2]=2;
        mask[2][0]=1;
        mask[2][1]=2;
        mask[2][2]=1;
        *//*
        generateGaussian(mask,mask_size);
    }
    if(filter_number==2)
    {
        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
            mask[i][j]=1;
    }






    for(y=0;y<width;y++)
        for(x=0;x<height;x++)
    {
        blue=0;
        red=0;
        green=0;
        weight=0;


        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
        {

            if(y-r+i>-1&&y-r+i<width)
                if(x-r+j>-1 && x-r+j <height)
                {

                    image2.pixel(y-r+i,x-r+j,color);

                    blue=blue+color.blue*mask[i][j];
                    red=red+color.red*mask[i][j];
                    green=green+color.green*mask[i][j];
                    weight=weight+mask[i][j];

                }

        }


        add.blue=blue/weight;
        add.red=red/weight;
        add.green=green/weight;

        image.set_pixel(y,x,add);
    }


    return 0;
}*/

int Picture::imageOpen(const QString name)
{

    image.load(name);
    height=image.height();
    width=image.width();
    return 0;
}




void Picture::grayscaling()
{
    QRgb color;
    int r;
    int b;
    int g;
    float gray;

    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {

        color=image.pixel(x,y);
        r=qRed(color);
        b=qBlue(color);
        g=qGreen(color);
        gray=(r+b+g)/3;

        image.setPixelColor(x,y,qRgb(gray,gray,gray));


    }


}

void Picture::printHistogram()
{
    int i;
    for(i=0;i<256;i++)
    {
        std::cout <<histogram.red[i]<< " " <<histogram.blue[i]<<  " " << histogram.green[i] << std::endl;
    }
}

void Picture::generateHistogram()
{


    histogram.red = new int [256];
    histogram.blue = new int [256];
    histogram.green = new int [256];
    array_clean(histogram.red);
    array_clean(histogram.blue);
    array_clean(histogram.green);



    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {
        QRgb color;

        color=image.pixel(x,y);
        histogram.red[qRed(color)]++;
        histogram.blue[qBlue(color)]++;
        histogram.green[qGreen(color)]++;

    }


}


void Picture::lightening(int scale)
{


    QRgb color;

    int r;
    int g;
    int b;

    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {

        color=image.pixel(x,y);

        if (qRed(color)+scale<=255 &&  qRed(color)+scale>0)
        r = qRed(color) +scale;
        else if (qRed(color)+scale>255) r= 255;
        else r=0;

        if (qBlue(color)+scale<=255 &&  qBlue(color)+scale>0)
        b = qBlue(color) +scale;
        else if (qBlue(color)+scale>255) b= 255;
        else b=0;

        if (qGreen(color)+scale<=255 &&  qGreen(color)+scale>0)
        g = qGreen(color) +scale;
        else if (qGreen(color)+scale>255)g= 255;
        else  g= 0;


        image.setPixelColor(x,y,qRgb(r,g,b));


    }
}

void Picture::contrast (int set)
{
    QRgb color;
    int r;
    int g;
    int b;

    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {

        color=image.pixel(x,y);

        if (set*(qRed(color)-178)+178<=255 &&  set*(qRed(color)-178)+178>0)
        r = set*(qRed(color)-178)+178;
        else if (qRed(color)+scale>255) r= 255;
        else r=0;

        if (set*(qBlue(color)-178)+178<=255 &&  set*(qBlue(color)-178)+178>0)
        b = set*(qBlue(color)-178)+178;
        else if (qBlue(color)+scale>255) b= 255;
        else b=0;


        if (set*(qGreen(color)-178)+178<=255 &&  set*(qGreen(color)-178)+178>0)
        g = set*(qGreen(color)-178)+178;
        else if (qGreen(color)+scale>255) g= 255;
        else g=0;

        image.setPixelColor(x,y,qRgb(r,g,b));


    }
}

int Picture::imageSave(const QString path)
{
    image.save(path);
    return 0;
}

void array_clean(int * array_h)
{
    int i;
    for(i=0;i<256;i++)
        array_h[i]=0;
}





void generateGaussian(double ** matrix,int mask_size)
{
    double sigma=1;
    double r,s = 2*sigma*sigma;

    double sum;

    int t = floor(mask_size/2);



    for (int x = -t; x <= t; x++)
    {
        for(int y = -t; y <= t; y++)
        {
            r = sqrt(x*x + y*y);
            matrix[x+t][y+t] = (exp(-(r*r)/s))/(M_PI * s);
            sum += matrix[x+t][y+t];
        }
    }


   for(int i = 0; i < mask_size; ++i)
     for(int j = 0; j < mask_size; ++j)
           matrix[i][j] /= sum;

    for(int i = 0; i < mask_size; ++i)
    {
        for (int j = 0; j < mask_size; ++j)
            std::cout<<matrix[i][j]<<"\t";
        std::cout<<std::endl;
    }


}

void Picture::imageCopy(int width,int height,Picture image,Picture new_image)
{
    QRgb color;

    for(size_t x=0;x<width;x++)
        for(size_t y=0;y<height;y++)
        {
            color=image.image.pixel(x,y);
            new_image.image.setPixelColor(x,y,color);
         }



}

