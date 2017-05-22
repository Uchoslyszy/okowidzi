#include<iostream>
#include "bitmap_image.hpp"
#include<stdlib.h>
#include "imageheader.h"


void array_clean(int * array_h)
{
    int i;
    for(i=0;i<16;i++)
        array_h[i]=0;
}


Picture::~Picture()
{
    if(histogram!=NULL)
        delete(histogram);

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

bitmap_image Picture::grayscaling()
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

    return image;
}



int Picture::generate_histogram()
{


    histogram = new int[16];
    array_clean(histogram);



    unsigned int height = image.height();
    unsigned int width = image.width();




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

    return 1;
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

/*int main()
{
    Picture obrazek;
    obrazek.image_open("input.bmp");
    obrazek.grayscaling();
    obrazek.generate_histogram();

    obrazek.image_save("output.bmp");
    obrazek.lightening(20);
    obrazek.image_save("output2.bmp");


    return 0;


}
*/
