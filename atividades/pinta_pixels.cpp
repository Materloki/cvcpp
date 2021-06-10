#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
using namespace std;
using namespace cv;


int distancia(Mat *three_channels, int l, int c, int bs, int gs, int rs){
    int dr = three_channels[0].at<uchar>(l, c) - bs;
    int dg = three_channels[1].at<uchar>(l, c) - gs;
    int db = three_channels[2].at<uchar>(l, c) - rs;
    return cvRound( sqrt( double(pow(dr ,2)+
                                 pow(dg ,2)+
                                 pow(db ,2)) ) );
} 



Mat pinta_pixels(Mat image, int l_semente, int c_semente, int t){
    Mat painted_image ;
    Mat three_channels[3];
    int rs, gs, bs;
    split(image,three_channels);

    bs = three_channels[0].at<uchar>(l_semente, c_semente);
    gs = three_channels[1].at<uchar>(l_semente, c_semente);
    rs = three_channels[2].at<uchar>(l_semente, c_semente);    
    queue<int> q;
    q.push(l_semente);
    q.push(c_semente);
    while(!q.empty()) {
        int l = q.front();
        q.pop();
        int c = q.front();
        q.pop();
        
        if(distancia(three_channels, l, c, bs, gs, rs) < t) {
            // pinta de vermelho (seguindo BGR)
            three_channels[0].at<uchar>(l, c) = 0;
            three_channels[1].at<uchar>(l, c) = 0;
            three_channels[2].at<uchar>(l, c) = 255;

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
    vector<Mat> channels;
    channels.push_back(three_channels[0]);
    channels.push_back(three_channels[1]);
    channels.push_back(three_channels[2]);
    merge(channels,painted_image);
    return painted_image;
}

int main() {
    Mat mickey, painted_mickey;
    mickey = imread("basico/elefante.jpg",IMREAD_COLOR);

    if (!mickey.data) {
        printf("No image data \n");
        return -1;
    }

    painted_mickey = pinta_pixels(mickey,  118, 131, 50);

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", painted_mickey);
    waitKey(0);
    imwrite("painted_mickey.bmp",painted_mickey);
    return 0;

}