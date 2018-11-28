//
// Created by LuLetterU on 2018/11/18.
//
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#define M 1280
#define NUMBER 1000
cv::Mat ellipse = cv::Mat::zeros(M, M, CV_8UC3);
cv::Mat line = cv::Mat::zeros(M, M, CV_8UC3);
cv::String ellipseWindowName = "DrawingImage";
cv::String lineWindowName = "LineImage";
cv::RNG rng(0xFFFFFFFF);

int x_1 = 0,x_2 = M;
int y_1 = 0, y_2 = M;

int ellipse_max_angle = 360, ellipse_angle = 0;

static cv::Scalar ramdomColor(cv::RNG & rng){
    int icolor = (unsigned) rng;
    return cv::Scalar(icolor & 256, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

int Drawing_Ramdom_Lines(cv::Mat &img, const cv::String windowName, cv::RNG &rng) {
    int lineType = 8;
    int tickness =2 ;
    cv::Point  begin ,end;
    for (int i = 0; i < NUMBER; ++i) {
        begin.x = rng.uniform(x_1, x_2);
        begin.y = rng.uniform(y_1, y_2);
        end.x = rng.uniform(x_1, x_2);
        end.y = rng.uniform(y_1, y_2);
        cv::line(img, begin, end, ramdomColor(rng), tickness, lineType);
        cv::imshow(windowName, img);
        if (cv::waitKey(20) >= 0) {
            return -1;
        }
    }
    return 0 ;
}


int Drawing_Random_Rectangle(cv::Mat &img, const cv::String windowName, cv::RNG &rng){
    int lineType = 0;
    int thickness  = 2;
    cv::Point ptr1 , ptr2;
    for (int i = 0; i < NUMBER; ++i) {
        ptr1.x = rng.uniform(x_1, x_2);
        ptr2.x = rng.uniform(x_1, x_2);
        ptr1.y = rng.uniform(y_1, y_2);
        ptr2.y = rng.uniform(y_1, y_2);
        cv::rectangle(img, ptr1, ptr2, ramdomColor(rng), thickness, lineType);
        cv::imshow(windowName, img);
        if (cv::waitKey(20) >= 0) {
            return -1;
        }
    }
    return 0;
}

void MyEllipse(cv::Mat img, int angle){
    int thickness = 2;
    int lineType = 8;
    cv::ellipse(img, cv::Point(M / 2, M / 2), cv::Size(M / 4, M / 16), angle, 0, 360, cv::Scalar(255, 0, 0), thickness,
                lineType);
    //cv::imshow(ellipseWindowName, ellipse);
}


void MyFilledCircle(cv::Mat &img, cv::Point center){
    cv::circle(img, center, M / 32, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
}


void MyPolygon(cv::Mat &img){
    int lineType = cv::LINE_8;
    cv::Point rook_points[1][20];
}

void MyLine(cv::Mat img, const cv::Point &start, const cv::Point &end){
    int thickness =2 ;
    int lineType = cv::LINE_8;
    cv::line(img, start, end, cv::Scalar(0, 0, 0), thickness, lineType);
}

static void  on_trackbar_touched_replot_ellipse(int, void *){
    MyEllipse(ellipse, ellipse_angle);
    printf("Ellipse angle trace bar is touched\n");
    cv::imshow(ellipseWindowName, ellipse);
}

TEST(BASIC_DRAWING_TEST, test_basic_draing) {

    //MyEllipse(ellipse, 50);
    cv::namedWindow(ellipseWindowName,CV_WINDOW_AUTOSIZE);
    //cv::createTrackbar("EllipseAngle", ellipseWindowName, &ellipse_angle, ellipse_max_angle,
                     //  on_trackbar_touched_replot_ellipse);
    MyEllipse(ellipse, 90);
    //cv::waitKey(0);
     MyEllipse(ellipse, 0);
    //cv::waitKey(0);
    MyEllipse(ellipse, 45);
    MyEllipse(ellipse, -45);
    cv::imshow(ellipseWindowName,ellipse);
    cv::waitKey(0);
}

TEST(BASIC_DRAWING_TEST,test_draw_line){
    cv::namedWindow(lineWindowName, CV_WINDOW_AUTOSIZE);
    MyLine(line, cv::Point(0, 15 * M / 16), cv::Point(M, 15 * M / 16));
    MyLine(line, cv::Point(M / 4, 7 * M / 8), cv::Point(M / 4, M));
    MyLine(line, cv::Point(M / 2, 7 * M / 8), cv::Point(M / 2, M));
    MyLine(line, cv::Point(3 * M / 2, 7 * M / 8), cv::Point(3 * M / 4, M));
    cv::imshow(lineWindowName, line);
    cv::waitKey(0);
}

TEST(BASIC_DRAWING_TEST,test_draw_ramdom_lines){
    cv::String windowsNameOfRamdomLines = "RamdomLines";
    cv::namedWindow(windowsNameOfRamdomLines, CV_WINDOW_AUTOSIZE);
    cv::Mat img = cv::Mat::zeros(M, M, CV_8UC3);
    Drawing_Ramdom_Lines(img, windowsNameOfRamdomLines, rng);
}
TEST(BASIC_DRAWING_TEST,test_draw_random_rectangles){
    cv::String windowNameofRandomRectangle = "RandomRectangles";
    cv::namedWindow(windowNameofRandomRectangle, CV_WINDOW_AUTOSIZE);
    cv::Mat img = cv::Mat::zeros(M, M, CV_8UC3);
    Drawing_Random_Rectangle(img, windowNameofRandomRectangle, rng);
}
