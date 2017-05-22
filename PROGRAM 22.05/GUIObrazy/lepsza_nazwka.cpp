#include<iostream>
#include <QApplication>
#include "bitmap_image.hpp"
#include <stdlib.h>
#include "imageheader.h"
#include "mainwindow.h"


bitmap_image grayscaling(bitmap_image image)
{
    unsigned int height = image.height();
    unsigned int width = image.width();



    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {
        rgb_t colour;
        rgb_t gray;
        image.get_pixel(x,y,colour);
        gray.red = (colour.red+colour.blue+colour.green)/3;
        gray.blue = (colour.red+colour.blue+colour.green)/3;
        gray.green = (colour.red+colour.blue+colour.green)/3;

        image.set_pixel(x,y,gray);


    }

    return image;
}

void array_clean(int * histogram)
{
    int i;
    for(i=0;i<16;i++)
        histogram[i]=0;
}

int * generate_histogram(bitmap_image image)
{

    int * histogram;
    histogram = new int[16];
    array_clean(histogram);



    unsigned int height = image.height();
    unsigned int width = image.width();

    int pixel_count=0;


    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {
        rgb_t colour;

        image.get_pixel(x,y,colour);

        if(colour.red<=16)
            histogram[0]++;
        else if(colour.red<=32 && colour.red>16)
            histogram[1]++;
        else if(colour.red<=48 && colour.red>32)
            histogram[2]++;
        else if(colour.red<=64 && colour.red>48)
            histogram[3]++;
        else if(colour.red<=80 && colour.red>64)
            histogram[4]++;
        else if(colour.red<=96 && colour.red>80)
            histogram[5]++;
        else if(colour.red<=112 && colour.red>96)
            histogram[6]++;
        else if(colour.red<=128 && colour.red>112)
            histogram[7]++;
        else if(colour.red<=144 && colour.red>128)
            histogram[8]++;
        else if(colour.red<=160 && colour.red>144)
            histogram[9]++;
        else if(colour.red<=176 && colour.red>160)
            histogram[10]++;
        else if(colour.red<=192 && colour.red>176)
            histogram[11]++;
        else if(colour.red<=208 && colour.red>192)
            histogram[12]++;
        else if(colour.red<=224 && colour.red>208)
            histogram[13]++;
        else if(colour.red<=240 && colour.red>224)
            histogram[14]++;
        else if(colour.red>=240)
            histogram[15]++;


    }

    return histogram;
}

bitmap_image lightening (bitmap_image image, int scale)
{
    unsigned int height =image.height();
    unsigned int width = image.width();

    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {
        rgb_t colour;
        rgb_t brighter;
        image.get_pixel(x,y,colour);

        if (colour.red+scale<255 &&  colour.red+scale>0)
        brighter.red = colour.red +scale;
        else if (colour.red+scale>0) brighter.red=255;
        else brighter.red=0;

        if (colour.blue+scale<255 &&  colour.blue+scale>0)
        brighter.blue = colour.blue +scale;
        else if (colour.blue+scale>0) brighter.blue=255;
        else brighter.blue=0;

        if (colour.green+scale<255 &&  colour.green+scale>0)
        brighter.green = colour.green +scale;
        else if (colour.green+scale>0) brighter.green=255;
        else brighter.green=0;

        image.set_pixel(x,y,brighter);
     }
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int x;
    unsigned int number=0;
    int * histogram;
  /*  bitmap_image image("input.bmp");
    if(!image)
    {
        std::cout << "cos nie wyszlo(obrazek sie nie wczytal) ";
        return -1;
    }

    image=grayscaling(image);
    histogram=generate_histogram(image);

    image.save_image("output.bmp");
    for(x=0;x<16;x++)
        printf("%i.: %i\n",x+1,histogram[x]);

    for(x=0;x<16;x++)
        number=number+histogram[x];

    printf("%i",number);   */
    return a.exec();


}
