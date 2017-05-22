#include<iostream>
#include "bitmap_image.hpp"
#include<stdlib.h>
#include "imageheader.h"





Picture::~Picture()
{
    if(histogram.red!=NULL)
        delete(histogram.red);
    if(histogram.blue!=NULL)
        delete(histogram.red);
    if(histogram.green!=NULL)
        delete(histogram.red);

}


int Picture::image_open(std::string name)
{
    bitmap_image picture(name);
    if(!picture)
    {
        printf("nie udalo sie wczytac obrazka");
        return -1;
    }
    image=picture;
    height=image.height();
    width=image.width();
    return 0;
}

int Picture::grayscaling()
{
    rgb_t colour;
    rgb_t gray;

    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {

        image.get_pixel(x,y,colour);
        gray.red = (colour.red+colour.blue+colour.green)/3;
        gray.blue = (colour.red+colour.blue+colour.green)/3;
        gray.green = (colour.red+colour.blue+colour.green)/3;

        image.set_pixel(x,y,gray);


    }

    return 0;
}



int Picture::generate_histogram()
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
        rgb_t colour;

        image.get_pixel(x,y,colour);
        histogram.red[colour.red]++;
        histogram.blue[colour.blue]++;
        histogram.green[colour.green]++;

    }

    return 0;
}

void Picture::lightening(int scale)
{


    rgb_t colour;
    rgb_t brighter;

    for(std::size_t y=0; y<height; y++)
        for(std::size_t x=0;x<width; x++)
    {

        image.get_pixel(x,y,colour);

        if (colour.red+scale<255 &&  colour.red+scale>0)
        brighter.red = colour.red +scale;
        else if (colour.red+scale>255) brighter.red=255;
        else brighter.red=0;

        if (colour.blue+scale<255 &&  colour.blue+scale>0)
        brighter.blue = colour.blue +scale;
        else if (colour.blue+scale>255) brighter.blue=255;
        else brighter.blue=0;

        if (colour.green+scale<255 &&  colour.green+scale>0)
        brighter.green = colour.green +scale;
        else if (colour.green+scale>255) brighter.green=255;
        else brighter.green=0;
        image.set_pixel(x,y,brighter);


    }
}

int Picture::image_save(std::string path)
{
    image.save_image(path);
    return 0;
}


void array_clean(int * array_h)
{
    int i;
    for(i=0;i<256;i++)
        array_h[i]=0;
}

