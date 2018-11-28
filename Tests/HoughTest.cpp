//
// Created by LuLetterU on 2018/11/11.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <string.h>
struct Vec3fSortComponent{
    bool operator() (const cv::Vec3f &v1, const cv::Vec3f &v2){
        return v1[2] > v2[2];
    }
} vec3fSortComponent;

TEST(Hough_TEST,hough_circle_demo){
    cv::Mat img = cv::imread("press/IMG_7586.JPG");
    cv::Mat resized_img,blurred,gray, edges;
    std::vector<cv::Vec3f> circles;
    cv::resize(img, resized_img, cv::Size(0, 0), 0.2, 0.2);
    cv::GaussianBlur(resized_img, blurred, cv::Size(3, 3), 0);
    cv::cvtColor(blurred, gray, cv::COLOR_RGB2GRAY, 1);
    //cv::imshow("GrayImage", gray);
    cv::Canny(gray, edges, 50, 150);
    //cv::imshow("CannyWind", edges);
    //cv::Mat pyrDownEdges;
    //cv::resize(edges, pyrDownEdges, cv::Size(), 0.2, 0.2, cv::INTER_LINEAR);
    //cv::imshow("CannyEdgesPyrDown", pyrDownEdges);
    cv::HoughCircles(edges, circles, cv::HOUGH_GRADIENT, 1, edges.rows/2 , 100, 100, 10, edges.rows/2);
    std::cout<< "Circle num is "<< circles.size()<< std::endl;
    std::sort(circles.begin(), circles.end(), vec3fSortComponent);
    for (size_t i = 0; i < circles.size(); ++i) {
        cv::circle(resized_img, cv::Point(cvRound(circles[i][0]),cvRound(circles[i][1])),
                   cvRound(circles[0][2]),
                   cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }
    cv::Mat resized_hough_img;
    cv::resize(img, resized_hough_img, cv::Size(), 0.2, 0.2, cv::INTER_LINEAR);
    cv::imshow("Hough Circles", resized_img);
    if (cv::waitKey() == 27) {
        cv::destroyAllWindows();
    }
}


/**
 *  Had validated that it is not work when the image is too large.
 *  The image must be shifed 0.2 double times smaller than before,or the Hough circle transition algorithm will run infinitely.
 */
TEST(Hough_TEST,hough_circle_demo_no_resize_test){
    clock_t start = clock();
    cv::Mat img = cv::imread("press/IMG_7586.JPG");
    cv::Mat blurred,edges,gray;
    if (img.data == NULL) {
        std::cout << "Empty Image." << std::endl;
        return;
    }
    std::vector<cv::Vec3f> circles;
    cv::GaussianBlur(img, blurred, cv::Size(), 0.2, 0.2);
    cv::cvtColor(blurred, gray, cv::COLOR_RGB2GRAY,1);
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, 100, 100, 100, 10, edges.rows / 2);
    std::cout << "Circle num is " << circles.size()<<std::endl;
    std::sort(circles.begin(), circles.end(), vec3fSortComponent);
    for (int i = 0; i < circles.size(); ++i) {
        cv::circle(img, cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1])), cvRound(circles[0][2]),
                   cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }
    cv::Mat resize_plot_img;
    cv::resize(img, resize_plot_img, cv::Size(), 0.2, 0.2);
    cv::imshow("HoughImage", resize_plot_img);
    clock_t end = clock();
    const double work_time = (start - end) / double(CLOCKS_PER_SEC);
    ASSERT_TRUE(work_time <= 2);
}



TEST(Hough_TEST,hough_circle_demo_resized_test){
    clock_t start = clock();
    cv::Mat img = cv::imread("press/IMG_7586.JPG");
    cv::Mat resized_img,blurred,edges,gray;
    if (img.data == NULL) {
        std::cout << "Empty Image." << std::endl;
        return;
    }
    cv::resize(img, resized_img, cv::Size(), 0.2, 0.2);
    std::vector<cv::Vec3f> circles;
    cv::GaussianBlur(resized_img, blurred, cv::Size(), 0.2, 0.2);
    cv::cvtColor(blurred, gray, cv::COLOR_RGB2GRAY,1);
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 2, 100, 100, 10, gray.rows / 2);
    std::cout << "Circle num is " << circles.size()<<std::endl;
    std::sort(circles.begin(), circles.end(), vec3fSortComponent);
    cv::Mat plotImg = resized_img.clone();
    for (int i = 0; i < circles.size(); ++i) {
        cv::circle(plotImg, cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1])), cvRound(circles[0][2]),
                   cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }
    cv::imshow("Hough Image Circle", plotImg);
    clock_t end = clock();
    const double work_time = (end - start) / double(CLOCKS_PER_SEC);
    std::cout<< "Execute Time :" << work_time<< std::endl;
    ASSERT_TRUE(work_time <= 2);
    int x = static_cast<int>(circles[0][0]), y = static_cast<int>(circles[0][1]), r = static_cast<int>(circles[0][2]);
    cv::Mat ROI = resized_img(cv::Rect(x - r, y - r, 2 * r, 2 * r));
    cv::imshow("ROI", ROI);

    cv::Mat ROIYUV;
    //cv::cvtColor(ROI,ROIYUV,cv::COLOR_BG)
    if (cv::waitKey() == 27) {
        cv::destroyAllWindows();
    }
}
