#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
       Mat inImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
 if (inImg.empty())
 {
  cout << "Error: cannot load source image!\n";
  return -1;
 }
        imshow ("Input Image", inImg);

     Mat smoothed_img = inImg.clone();
        for(int i = 1 ; i < 10; i ++){
     GaussianBlur(inImg,smoothed_img,Size(2*i+1,2*i+1),1.5);
   }
        imshow("Output Image", smoothed_img);

        return 0;
}
