#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main (int argc, const char** argv)
{
 Mat inImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
if (inImg.empty())
 {
  cout << "Error: cannot load source image!\n";
  return -1;
 }
 Mat smoothed_img = in_Img.clone();
        imshow ("Input Image", inImg);
  for(int i = 1 ; i < 10; i ++){

    medianBlur(img,smoothed_img,2*i+1);
  }
 imshow("Output Image", smoothed_img);
  return 0;
}
