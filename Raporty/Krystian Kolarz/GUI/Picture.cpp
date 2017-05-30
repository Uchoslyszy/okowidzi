#include<iostream>
#include<stdlib.h>
#include "Picture.h"
#include<math.h>
#include<QImage>
#include<QRgb>
#include<QString>
#include<cmath>




Picture::Picture(const QString name)
{
    image.load(name);
    height=image.height();
    width=image.width();
    histogram.blue=new int[256];
    histogram.red=new int[256];
    histogram.green=new int[256];
}

Picture::Picture()
{
    histogram.blue=new int[256];
    histogram.red=new int[256];
    histogram.green=new int[256];
}

Picture::Picture(int width,int height,QImage::Format format)
{
    new (&image)QImage(width,height,format);
    height=image.height();
    width=image.width();
    histogram.blue=new int[256];
    histogram.red=new int[256];
    histogram.green=new int[256];
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

int Picture::Width()
{
    return width;
}

int Picture::Height()
{
    return height;
}

QImage::Format Picture::format()
{
    return image.format();
}

int Picture::equalFilter(int mask_size)
{
    int r = floor(mask_size/2);

    int i,x,y,j;
    double blue,red,green,weight;

    QRgb color;

    Picture image2(image.width(),image.height(),image.format());
    image2.imageCopy(image.width(),image.height(),*this);

    double ** mask;
    mask = new double*[mask_size];
    for(i=0;i<mask_size;i++)
        mask[i] = new double[mask_size];

        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
            mask[i][j]=1;

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
                    color=image2.image.pixel(y-r+i,x-r+j);

                    blue=blue+qBlue(color)*mask[i][j];
                    red=red+qRed(color)*mask[i][j];
                    green=green+qGreen(color)*mask[i][j];
                    weight=weight+mask[i][j];
                }
        }

        blue=floor(blue/weight);
        red=floor(red/weight);
        green=floor(green/weight);

        image.setPixelColor(y,x,qRgb(red,green,blue));
    }
    for(i=0;i<mask_size;i++)
        delete(mask[i]);
    delete(mask);
    return 0;
}

int Picture::imageOpen(const QString name)
{
    image.load(name);
    height=image.height();
    width=image.width();
    return 0;
}


int Picture::gaussianBlur(int mask_size,double sigma)
{
    int r = floor(mask_size/2);

    int i,x,y,j;
    double blue,red,green,weight;

    QRgb color;

    Picture image1(image.width(),image.height(),image.format());
    image1.imageCopy(image.width(),image.height(),*this);

    double ** mask;
    mask = new double*[mask_size];
    for(i=0;i<mask_size;i++)
        mask[i] = new double[mask_size];


    if(generateGaussian(mask,mask_size,sigma)==-1)
    {
        std::cout << "zly rozmiar maski dla filtra gausowskiego";
        return -1;
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
                    color=image1.image.pixel(y-r+i,x-r+j);

                    blue=blue+qBlue(color)*mask[i][j];
                    red=red+qRed(color)*mask[i][j];
                    green=green+qGreen(color)*mask[i][j];
                    weight=weight+mask[i][j];
                }
         }

        blue=floor(blue/weight);
        red=floor(red/weight);
        green=floor(green/weight);

        image.setPixelColor(y,x,qRgb(red,green,blue));
    }
    for(i=0;i<mask_size;i++)
        delete(mask[i]);
    delete(mask);

    return 0;
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
        else if (set*(qRed(color)-178)+178>255) r= 255;
        else r=0;

        if (set*(qBlue(color)-178)+178<=255 &&  set*(qBlue(color)-178)+178>0)
        b = set*(qBlue(color)-178)+178;
        else if (set*(qBlue(color)-178)+178>255) b= 255;
        else b=0;


        if (set*(qGreen(color)-178)+178<=255 &&  set*(qGreen(color)-178)+178>0)
        g = set*(qGreen(color)-178)+178;
        else if (set*(qGreen(color)-178)+178>255) g= 255;
        else g=0;

        image.setPixelColor(x,y,qRgb(r,g,b));
    }
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



int generateGaussian(double ** matrix,int mask_size,double sigma)
{
    if(mask_size%2==0)
    {
        std::cout << "nie mozna utworzyc maski o parzystej wielkosci";
                     return -1;
    }

    double r,s = 2*sigma*sigma;

    double sum=0;

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
         {
              matrix[i][j] = matrix[i][j]/sum;
        }
    return 0;
}

void Picture::imageCopy(int width,int height,Picture image2)
{
    QRgb color;

    for(size_t x=0;x<width;x++)
        for(size_t y=0;y<height;y++)
        {
            color=image2.image.pixel(x,y);
            image.setPixelColor(x,y,color);
         }
}

QImage Picture::imagePointer()
{
    return image;
}

void Picture::pixelizeFilter(int mask_size)
{
    int r = floor(mask_size/2);

    int i,x,y,j,count;
    double blue,red,green,weight;
    Picture image2(image.width(),image.height(),image.format());
    image2.imageCopy(image.width(),image.height(),*this);

    QRgb color;
        y=0;
        while(y<width)
        {
            x=0;
            while(x<height)
        {
            blue=0;
            red=0;
            green=0;
            weight=0;
            count =0;

            for(i=0;i<mask_size;i++)
                for(j=0;j<mask_size;j++)
            {

                if(y-r+i>-1&&y-r+i<width)
                    if(x-r+j>-1 && x-r+j <height)
                    {

                        color=image2.image.pixel(y-r+i,x-r+j);

                        blue=blue+qBlue(color);
                        red=red+qRed(color);
                        green=green+qGreen(color);
                        count++;
                   }
            }
            blue=floor(blue/(count));
            red=floor(red/(count));
            green=floor(green/(count));

            for(i=0;i<mask_size;i++)
                for(j=0;j<mask_size;j++)
            {

                if(y-r+i>-1&&y-r+i<width)
                    if(x-r+j>-1 && x-r+j <height)
                    {
                        image.setPixelColor(y-r+i,x-r+j,qRgb(red,green,blue));
                    }
            }

           x+=mask_size;
           if(x>height-1)
           {
               blue=0;
               red=0;
               green=0;
               weight=0;
               count =0;
               for(i=0;i<mask_size;i++)
                   for(j=0;j<mask_size;j++)
               {

                   if(y-r+i>-1&&y-r+i<width)
                       if(x-r+j>-1 && x-r+j <height)
                       {
                           color=image2.image.pixel(y-r+i,x-r+j);

                           blue=blue+qBlue(color);
                           red=red+qRed(color);
                           green=green+qGreen(color);
                           count++;
                       }
               }

               blue=floor(blue/(count));
               red=floor(red/(count));
               green=floor(green/(count));

               for(i=0;i<mask_size;i++)
                   for(j=0;j<mask_size;j++)
               {
                   if(y-r+i>-1&&y-r+i<width)
                       if(x-r+j>-1 && x-r+j <height)
                       {
                           image.setPixelColor(y-r+i,x-r+j,qRgb(red,green,blue));
                       }
               }
           }
        }
            y+=mask_size;
            if(y>width-1)
            {
                x=0;
                while(x<height)
            {
                blue=0;
                red=0;
                green=0;
                weight=0;
                count =0;

                for(i=0;i<mask_size;i++)
                    for(j=0;j<mask_size;j++)
                {

                    if(y-r+i>-1&&y-r+i<width)
                        if(x-r+j>-1 && x-r+j <height)
                        {
                            color=image2.image.pixel(y-r+i,x-r+j);

                            blue=blue+qBlue(color);
                            red=red+qRed(color);
                            green=green+qGreen(color);
                            count++;

                        }
                }

                blue=floor(blue/(count));
                red=floor(red/(count));
                green=floor(green/(count));

                for(i=0;i<mask_size;i++)
                    for(j=0;j<mask_size;j++)
                {

                    if(y-r+i>-1&&y-r+i<width)
                        if(x-r+j>-1 && x-r+j <height)
                        {
                            image.setPixelColor(y-r+i,x-r+j,qRgb(red,green,blue));
                        }
                }
               x+=mask_size;
               if(x>height-1)
               {
               {
                   blue=0;
                   red=0;
                   green=0;
                   weight=0;
                   count =0;
                   for(i=0;i<mask_size;i++)
                       for(j=0;j<mask_size;j++)
                   {
                       if(y-r+i>-1&&y-r+i<width)
                           if(x-r+j>-1 && x-r+j <height)
                           {
                               color=image2.image.pixel(y-r+i,x-r+j);

                               blue=blue+qBlue(color);
                               red=red+qRed(color);
                               green=green+qGreen(color);
                               count++;

                           }
                   }

                   blue=floor(blue/(count));
                   red=floor(red/(count));
                   green=floor(green/(count));

                   for(i=0;i<mask_size;i++)
                       for(j=0;j<mask_size;j++)
                   {

                       if(y-r+i>-1&&y-r+i<width)
                           if(x-r+j>-1 && x-r+j <height)
                           {

                               image.setPixelColor(y-r+i,x-r+j,qRgb(red,green,blue));

                           }

                   }
               }
               }
            }
        }
        }

}

void Picture::medianFilter(int mask_size)
{
    int r = floor(mask_size/2);

    int i,x,y,j,count,cord;
    double blue,red,green,weight;
    QRgb color;

    double * values_blue;
    values_blue = new double[mask_size*mask_size];

    double * values_green;
    values_green = new double[mask_size*mask_size];

    double * values_red;
    values_red = new double[mask_size*mask_size];

    Picture image2(width,height,this->format());
    image2.imageCopy(width,height,*this);

    for(y=0;y<width;y++)
        for(x=0;x<height;x++)
    {
        blue=0;
        red=0;
        green=0;
        weight=0;
        count = 0;

        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
        {

            if(y-r+i>-1&&y-r+i<width)
                if(x-r+j>-1 && x-r+j <height)
                {

                    color=image2.image.pixel(y-r+i,x-r+j);

                    values_blue[count]=qBlue(color);
                    values_green[count]=qGreen(color);
                    values_red[count]=qRed(color);
                    count++;
                }
        }

        arraySort(values_blue,mask_size*mask_size);
        arraySort(values_green,mask_size*mask_size);
        arraySort(values_red,mask_size*mask_size);

        cord=ceil(count/2);
        blue=values_blue[cord];
        red=values_red[cord];
        green=values_green[cord];

        this->image.setPixelColor(y,x,qRgb(red,green,blue));
    }
    delete(values_blue);
    delete(values_green);
    delete(values_red);
}

void arraySort(double * values,int size)
{
    int i;
    int j;
    double temp;

    for(i=0;i<size-1;i++)
        for(j=0;j<size-1;j++)
        {
            if(values[j+1]<values[j])
            {

                temp=values[j];
                values[j]=values[j+1];
                values[j+1]=temp;
            }
    }
}


