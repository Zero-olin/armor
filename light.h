#pragma once
#include<iostream>
#include<vector>
#include <stdio.h>
#include<string>;
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
class light
{
private:
    Mat  channels[3], thresh_dst, Gauss_dst;
    vector<vector<Point>> contours;//点集
    vector<Vec4i> hierarchy;
    Rect bound_rect;
    RotatedRect box;
public:
    VideoCapture cap;
    Mat frame;
    light();//初始化
    void Read();
    void Split();
    void ThresHold();
    void gaussian();
    void Find();
    double get_fps(double a);
    void draw(double fps);
};