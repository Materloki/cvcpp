#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


Mat corrige_defeitos(Mat noised_image){
    
    Mat cleaned_image = noised_image.clone();

    int rows = noised_image.rows;
    int cols = noised_image.cols;
    for(int row = 1; row < rows; row++){
        for(int col = 1; col < cols; col++){
            if(cleaned_image.at<uchar>(row,col)==255){
                // Pontos brancos
                if(cleaned_image.at<uchar>(row,col-1) == 0 &&
                    cleaned_image.at<uchar>(row,col+1) == 0 ||
                    cleaned_image.at<uchar>(row-1,col) == 0 &&
                    cleaned_image.at<uchar>(row+1,col) == 0){
                        cleaned_image.at<uchar>(row,col) = 0;
                    } 
            }
            else{
                // Pontos pretos
                if(cleaned_image.at<uchar>(row,col-1) == 255 &&
                    cleaned_image.at<uchar>(row,col+1) == 255 ||
                    cleaned_image.at<uchar>(row-1,col) == 255 &&
                    cleaned_image.at<uchar>(row+1,col) == 255){
                        cleaned_image.at<uchar>(row,col) = 255;
                    } 
            }
        }
    }
    return cleaned_image;
}

int main(){
    Mat mickey, clean_mickey;
    mickey = imread("basico/mickey.bmp",IMREAD_GRAYSCALE);

    if ( !mickey.data )
    {
        printf("No image data \n");
        return -1;
    }
    clean_mickey = corrige_defeitos(mickey);

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", clean_mickey);
    waitKey(0);
    imwrite("cleaned_mickey.bmp",clean_mickey);
    return 0;
}