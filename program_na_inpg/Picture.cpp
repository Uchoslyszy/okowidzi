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
    imageHeight=image.height();
    imageWidth=image.width();
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

Picture::Picture(int newWidth,int newHeight,QImage::Format format)
{
    new (&image)QImage(newWidth,newHeight,format);
    this->imageHeight=image.height();
    this->imageWidth=image.width();
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
    std::cout<<"image is being deleted" << std::endl;

}

int Picture::getWidth()
{
    return imageWidth;
}

int Picture::getHeight()
{
    return imageHeight;
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

    Picture image2(this->imageWidth,this->imageHeight,this->format());
    image2.imageCopy(this->imageWidth,this->imageHeight,image);

    double ** mask;
    mask = new double*[mask_size];
    for(i=0;i<mask_size;i++)
        mask[i] = new double[mask_size];



        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
            mask[i][j]=1;


    for(y=0;y<imageWidth;y++)
        for(x=0;x<imageHeight;x++)
    {
        blue=0;
        red=0;
        green=0;
        weight=0;


        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
        {

            if(y-r+i>-1&&y-r+i<imageWidth)
                if(x-r+j>-1 && x-r+j <imageHeight)
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
    imageHeight=image.height();
    imageWidth=image.width();
    return 0;
}


int Picture::gaussianBlur(int mask_size,double sigma)
{
    int r = floor(mask_size/2);

    int i,x,y,j;
    double blue,red,green,weight;

    QRgb color;

    Picture image2(image.width(),image.height(),image.format());
    image2.imageCopy(image.width(),image.height(),image);

    double ** mask;
    mask = new double*[mask_size];
    for(i=0;i<mask_size;i++)
        mask[i] = new double[mask_size];


    if(generateGaussian(mask,mask_size,sigma)==-1)
    {
        std::cout << "zly rozmiar maski dla filtra gausowskiego";
        return -1;
    }

    for(y=0;y<imageWidth;y++)
        for(x=0;x<imageHeight;x++)
    {
        blue=0;
        red=0;
        green=0;
        weight=0;


        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
        {

            if(y-r+i>-1&&y-r+i<imageWidth)
                if(x-r+j>-1 && x-r+j <imageHeight)
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


void Picture::grayscaling()
{
    QRgb color;
    int r;
    int b;
    int g;
    float gray;

    for(std::size_t y=0; y<imageHeight; y++)
        for(std::size_t x=0;x<imageWidth; x++)
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



    for(std::size_t y=0; y<imageHeight; y++)
        for(std::size_t x=0;x<imageWidth; x++)
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

    for(std::size_t y=0; y<imageHeight; y++)
        for(std::size_t x=0;x<imageWidth; x++)
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


void Picture::imageCopy(int width,int height,QImage source_image)
{
    QRgb color;

    for(size_t x=0;x<width;x++)
        for(size_t y=0;y<height;y++)
        {
            color=source_image.pixel(x,y);
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
    Picture image2(this->imageWidth,this->imageHeight,image.format());
    image2.imageCopy(this->imageWidth,this->imageHeight,image);

    QRgb color;
        y=0;
        while(y<imageWidth)
        {
            x=0;
            while(x<imageHeight)
        {
            blue=0;
            red=0;
            green=0;
            weight=0;
            count =0;


            for(i=0;i<mask_size;i++)
                for(j=0;j<mask_size;j++)
            {

                if(y-r+i>-1&&y-r+i<imageWidth)
                    if(x-r+j>-1 && x-r+j <imageHeight)
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

                if(y-r+i>-1&&y-r+i<imageWidth)
                    if(x-r+j>-1 && x-r+j <imageHeight)
                    {

                        image.setPixelColor(y-r+i,x-r+j,qRgb(red,green,blue));

                    }

            }


           x+=mask_size;
           if(x>imageHeight-1)
           {
               blue=0;
               red=0;
               green=0;
               weight=0;
               count =0;
               for(i=0;i<mask_size;i++)
                   for(j=0;j<mask_size;j++)
               {

                   if(y-r+i>-1&&y-r+i<imageWidth)
                       if(x-r+j>-1 && x-r+j <imageHeight)
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

                   if(y-r+i>-1&&y-r+i<imageWidth)
                       if(x-r+j>-1 && x-r+j <imageHeight)
                       {

                           image.setPixelColor(y-r+i,x-r+j,qRgb(red,green,blue));

                       }

               }
           }



        }
            y+=mask_size;
            if(y>imageWidth-1)
            {

                x=0;
                while(x<imageHeight)
            {
                blue=0;
                red=0;
                green=0;
                weight=0;
                count =0;


                for(i=0;i<mask_size;i++)
                    for(j=0;j<mask_size;j++)
                {

                    if(y-r+i>-1&&y-r+i<imageWidth)
                        if(x-r+j>-1 && x-r+j <imageHeight)
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

                    if(y-r+i>-1&&y-r+i<imageWidth)
                        if(x-r+j>-1 && x-r+j <imageHeight)
                        {

                            image.setPixelColor(y-r+i,x-r+j,qRgb(red,green,blue));

                        }

                }

               x+=mask_size;
               if(x>imageHeight-1)
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

                       if(y-r+i>-1&&y-r+i<imageWidth)
                           if(x-r+j>-1 && x-r+j <imageHeight)
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

                       if(y-r+i>-1&&y-r+i<imageWidth)
                           if(x-r+j>-1 && x-r+j <imageHeight)
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
    double blue,red,green;
    QRgb color;


    double * values_blue;
    values_blue = new double[mask_size*mask_size];


    double * values_green;
    values_green = new double[mask_size*mask_size];


    double * values_red;
    values_red = new double[mask_size*mask_size];


    Picture image2(imageWidth,imageHeight,this->format());
    image2.imageCopy(imageWidth,imageHeight,image);

    for(y=0;y<imageWidth;y++)
        for(x=0;x<imageHeight;x++)
    {
        blue=0;
        red=0;
        green=0;

        count = 0;

        for(i=0;i<mask_size;i++)
            for(j=0;j<mask_size;j++)
        {

            if(y-r+i>-1&&y-r+i<imageWidth)
                if(x-r+j>-1 && x-r+j <imageHeight)
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

        if(count%2==0)
        {
            cord=ceil(count/2);
            blue=(values_blue[cord]+values_blue[cord+1])/2;
            red=(values_red[cord]+values_red[cord+1])/2;
            green=(values_green[cord]+values_green[cord+1])/2;
        }
        else
        {
            cord=ceil(count/2);
            blue=values_blue[cord];
            red=values_red[cord];
            green=values_green[cord];
        }



        this->image.setPixelColor(y,x,qRgb(red,green,blue));
    }
    delete(values_blue);
    delete(values_green);
    delete(values_red);
}

void Picture::contrast (double set)
{
    QRgb color;
    int r;
    int g;
    int b;


    for(std::size_t y=0; y<imageHeight; y++)
        for(std::size_t x=0;x<imageWidth; x++)
    {

        color=image.pixel(x,y);

        if (set*(qRed(color)-127)+127<=255 &&  set*(qRed(color)-127)+127>0)
        r = set*(qRed(color)-127)+127;
        else if (set*(qRed(color)-127)+127>255) r= 255;
        else r=0;

        if (set*(qBlue(color)-127)+127<=255 &&  set*(qBlue(color)-127)+127>0)
        b = set*(qBlue(color)-127)+127;
        else if (set*(qBlue(color)-127)+127>255) b= 255;
        else b=0;


        if (set*(qGreen(color)-127)+127<=255 &&  set*(qGreen(color)-127)+127>0)
        g = set*(qGreen(color)-127)+127;
        else if (set*(qGreen(color)-127)+127>255) g= 255;
        else g=0;

        image.setPixelColor(x,y,qRgb(r,g,b));


    }
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


