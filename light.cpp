#include<iostream>
#include<vector>
#include <stdio.h>
#include<string>;
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include"light.h"
using namespace std;
using namespace cv;
const int kThreash = 220;
const int kMaxval = 225;
const Size kGaussian = Size(5, 5);
const string path = "D:\\red_circle.mp4";

light::light()
{
    cap.open(0);
    //video.open(path);
}
void light::Read()
{
    cap.read(frame);
}
void light::Split()
{
    split(frame, channels);
}
void light::ThresHold()
{
    threshold(channels[2], thresh_dst, kThreash, kMaxval, 0);
}
void light::gaussian()
{
    GaussianBlur(thresh_dst, Gauss_dst, kGaussian, 0);
}
void light::Find()
{
    findContours(Gauss_dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
}
double light::get_fps(double a)
{
    a = ((double)getTickCount() - a) / getTickFrequency();
    double fps = 1.0 / a;
    return fps;
}
void light::draw(double fps)
{
    Rect point_array[20];
    
    int num = 0;
    for (int i = 0; i < contours.size(); i++)
    {

        bound_rect = boundingRect(contours[i]);
        //�����õ��������������ǵ�����������ͨ�������������ɸѡ������������
        if (double(bound_rect.height / bound_rect.width) >= 2)
        {
            point_array[num] = bound_rect;
            num++;
        }

    }
    int closest_point[2] = {};
    int min = 10000;//���������������ֵ���бȽϣ��ҳ���������������������Ϊ��������������
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = i + 1; j < num; j++) {
            int result = abs(point_array[i].area() - point_array[j].area());
            if (result < min)
            {
                min = result;
                closest_point[0] = i;
                closest_point[1] = j;
            }
        }
    }
    try
    {
        Rect rectangle_1 = point_array[closest_point[0]];
        Rect rectangle_2 = point_array[closest_point[1]];
        //rectangle_1��rectangle_2�������������ľ���
        if (rectangle_2.x == 0 || rectangle_1.x == 0) 
        {
            throw "none";
        }
        //��ȡ�����������,��������Ƶ��ÿ�������Ŀ�Ⱥ�С������ʹ�õ������е�������н��ƴ���
        Point point_1 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y);
        Point point_2 = Point(rectangle_1.x + rectangle_1.width / 2, rectangle_1.y + rectangle_1.height);
        Point point_3 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y);
        Point point_4 = Point(rectangle_2.x + rectangle_2.width / 2, rectangle_2.y + rectangle_2.height);
        Point p[4] = { point_1,point_2,point_4,point_3 };
        cout << fps << endl;
        //ͨ���Ĵ�ѭ��������������ע���ĸ������߽������ӣ��γɾ���
        for (int i = 0; i < 4; i++)
        {
            line(frame, p[i % 4], p[(i + 1) % 4], Scalar(0, 255, 0), 2);
        }
    }
    catch (const char* t)
    {
        cout << t << endl;
    }
}