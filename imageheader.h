#ifndef IMAGEHEADER_H
#define IMAGEHEADER_H

bitmap_image grayscaling(bitmap_image image);
void array_clean(int * histogram);
int * generate_histogram(bitmap_image image);
bitmap_image lightening (bitmap_image image, int scale);


#endif // IMAGEHEADER_H
