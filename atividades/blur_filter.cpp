#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
using namespace std;
using namespace cv;



int main() {
    Mat src, dst;
    src = imread("filtros/fever-2.pgm",IMREAD_GRAYSCALE);

    if (!src.data) {
        printf("No image data \n");
        return -1;
    }

    medianBlur(src, dst, 15);

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", dst);
    waitKey(0);
    imwrite("blured.png",dst);
    return 0;

}