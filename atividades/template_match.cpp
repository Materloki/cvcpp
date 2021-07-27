// Guilherme Fernandes Gonçalves Silva             NUSP 10297272
// Rodrigo Estevam de Paula                        NUSP 10773843

#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
using namespace std;
using namespace cv;

Mat_<float> somaAbsDois(Mat a) { // Faz somatoria absoluta da imagem dar dois
double soma = sum(abs(a))[0]; a /= (soma/2.0);
return a;
}

Mat_<float> dcReject(Mat a) { // Elimina nivel DC (subtrai media)
a=a-mean(a)[0];
return a;
}

Mat_<float> matchTemplateSame(Mat_<float> a, Mat_<float> q, int method, float backg=0.0) {
    Mat_<float> p{ a.size(), backg };
    Rect rect{ (q.cols-1)/2, (q.rows-1)/2, a.cols-q.cols+1, a.rows-q.rows+1};
    Mat_<float> roi{ p, rect };
    matchTemplate(a, q, roi, method);
    return p;
}



Mat match(Mat a, Mat q, float threshold){
    Mat_<uchar> temp;
    Mat_<float> q1=somaAbsDois(dcReject(q));
    Mat p1, result;
    p1 = matchTemplateSame(a, q1, TM_CCOEFF_NORMED);
    a.convertTo(temp, CV_8U, 255.0, 0.0);
    cvtColor(temp, result, COLOR_GRAY2RGB); 
    p1 = abs(p1); 
    for (int l=0; l<p1.rows; l++)
        for (int c=0; c<p1.cols; c++)
            if (p1.at<float>(l,c)>=threshold)
                circle(result, Point(c,l), 2, Scalar( 0, 0, 255 ), FILLED, LINE_8);
    return result;
}





int main(){
    Mat_<uchar> temp;
    Mat original = imread("tmatch/a.png");
    Mat_<float> a; temp=imread("tmatch/a.png",0); temp.convertTo(a,CV_32F,1.0/255.0,0.0);
    Mat_<float> q; temp=imread("tmatch/q.png",0); temp.convertTo(q,CV_32F,1.0/255.0,0.0);
    Mat result = match(a, q, 0.9);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", result);
    waitKey(0);
    imwrite("bear_found.png",result);
    return 0;
}