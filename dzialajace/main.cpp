#include "Picture.h"


int main()
{

    Picture image;

    image.imageOpen("C:/port_na_qt/port/input.bmp");//dajcie jakies wlasne sciezki


    image.gaussianBlur(5,3);
    image.imageSave("C:/port_na_qt/port/output1.bmp");
    image.pixelizeFilter(15);
    image.imageSave("C:/port_na_qt/port/output2.bmp");
    image.medianFilter(5);
    image.imageSave("C:/port_na_qt/port/output3.bmp");
    image.equalFilter(3);
    image.imageSave("C:/port_na_qt/port/output4.bmp");
    image.grayscaling();
    image.imageSave("C:/port_na_qt/port/output5.bmp");
    image.contrast(3,10);
    image.imageSave("C:/port_na_qt/port/output6.bmp");


    return 0;
}
