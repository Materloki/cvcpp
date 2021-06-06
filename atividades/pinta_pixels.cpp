#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
using namespace std;
using namespace cv;


Mat pinta_pixels(Mat image, int l_semente, int c_semente){
    
    Mat painted_image = image.clone();

    queue<int> q;
    q.push(l_semente);
    q.push(c_semente);

    while(!q.empty()) {
        l = q.front();
        q.pop();
        c = q.front();
        q.pop();

        if(painted_image.at<uchar>(l, c, 0) == 255 &&
            painted_image.at<uchar>(l, c, 1) == 255 &&
            painted_image.at<uchar>(l, c, 2) == 255) {
            
            // pinta de azul
            painted_image.at<uchar>(l, c, 0) = 255;
            painted_image.at<uchar>(l, c, 1) = 0;
            painted_image.at<uchar>(l, c, 2) = 0;

            // coloca vizinhos na fila
            q.push(l - 1);
            q.push(c);
            q.push(l + 1);
            q.push(c);
            q.push(l);
            q.push(c + 1);
            q.push(l);
            q.push(c - 1);
        }
    }
    return painted_image;
}

int main() {
    Mat mickey, clean_mickey;
    mickey = imread("basico/mickey.bmp",IMREAD_COLOR);

    if (!mickey.data) {
        printf("No image data \n");
        return -1;
    }
    painted_mickey = pinta_pixels(mickey, 20, 21);

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", painted_mickey);
    waitKey(0);
    imwrite("painted_mickey.bmp",painted_mickey);
    return 0;
}