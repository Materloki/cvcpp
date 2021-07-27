// Guilherme Fernandes Gonçalves Silva             NUSP 10297272
// Rodrigo Estevam de Paula                        NUSP 10773843

#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
using namespace std;
using namespace cv;

void resize_returns(Mat image){
    // Saves 4 images of the original resized by 4 different methods
    Mat nearest, linear, cubic, lanczos4;
    resize(image, nearest, Size(0,0), 3, 3, INTER_NEAREST);
    resize(image, linear, Size(0,0), 3, 3, INTER_LINEAR);
    resize(image, cubic, Size(0,0), 3, 3, INTER_CUBIC);
    resize(image, lanczos4, Size(0,0), 3, 3, INTER_LANCZOS4);

    imwrite("resize/lenna-nearest.png",nearest);
    imwrite("resize/lenna-linar.png",linear);
    imwrite("resize/lenna-cubic.png",cubic);
    imwrite("resize/lenna-lanczos4.png",lanczos4);
}


int main(){
    Mat img;
    img = imread("transformacao/lennag-reduz.jpg",IMREAD_COLOR);

    if ( !img.data )
    {
        printf("No image data \n");
        return -1;
    }
    resize_returns(img);
    return 0;
}