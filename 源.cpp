#include <stdio.h>
#include<iostream> 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<string>;
#include"light.h"
using namespace std;
using namespace cv;
int main()
{
    light L;
    vector<Point2f> boxPts(4);
    for (;;)
    {
        
        double f = (double)getTickCount();
        L.Read();
        double fps=L.get_fps(f);//ÇóÖ¡Êý
        L.Split();
        L.ThresHold();
        L.gaussian();
        L.Find();
        L.draw(fps);
        imshow("imshow", L.frame);
        waitKey(10);
    }
    L.cap.release();
    cv::destroyAllWindows();
    return 0;
}