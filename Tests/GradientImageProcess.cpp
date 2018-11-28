//
// Created by LuLetterU on 2018/11/19.
//
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

cv::Mat grad_src,grad_res;
cv::String sobelWindowName = "Sobel Demo";
cv::String scharrWindowName = "Scharr Demo";


TEST(TEST_IMGAE_GRADIENT,test_Sobel_operator){
    grad_src = cv::imread("rgb/1.jpg", cv::IMREAD_COLOR);
    if (!grad_src.data) {
        std::cout << "Open Image Error." << std::endl;
        return;
    }
    cv::namedWindow(scharrWindowName, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(scharrWindowName, -600, 500);
    cv::Mat scharr_src,scharr_res;
    scharr_src= grad_src.clone();
    cv::cvtColor(scharr_src, scharr_src, cv::COLOR_RGB2GRAY);
    cv::Mat scharr_grad_x,scharr_grad_y,abs_scharr_grad_x,abs_scharr_grad_y;
    cv::Scharr(scharr_src, scharr_grad_x , -1, 1, 0, 1, 0);
    cv::Scharr(scharr_src, scharr_grad_y, -1, 0, 1, 1);
    cv::convertScaleAbs(scharr_grad_x, abs_scharr_grad_x);
    cv::convertScaleAbs(scharr_grad_y, abs_scharr_grad_y);
    cv::addWeighted(scharr_grad_x, 0.5, scharr_grad_y, 0.5, 0, scharr_res);
    cv::imshow(scharrWindowName, scharr_res);


    cv::namedWindow(sobelWindowName, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(sobelWindowName, -600, 500);
    const int ddepth = -1;
    int delta = 0, scale = 1,ksize = -1;
    while(1){
        cv::Mat gray_src;
        cv::GaussianBlur(grad_src, grad_src, cv::Size(3, 3), 0, 0);
        cv::cvtColor(grad_src, gray_src, cv::COLOR_RGB2GRAY);
        cv::Mat grad_x, grad_y, abs_grad_x, abs_grad_y,grad;
        cv::Sobel(gray_src, grad_x, ddepth, 1, 0, ksize, scale, delta);
        cv::Sobel(gray_src, grad_y, ddepth, 0, 1, ksize, scale, delta);
        cv::convertScaleAbs(grad_x, abs_grad_x);
        cv::convertScaleAbs(grad_y, abs_grad_y);
        cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
        cv::imshow(sobelWindowName, grad);
        char key = static_cast<char>(cv::waitKey(0));
        if (key == 27) {
            break;
        } else if (key == 'k' || key =='K') {
            ksize = ksize > 30 ? -1 : ksize + 2;
        } else if (key == 's' || key == 'S') {
            scale = scale +1;
        } else if (key == 'd' || key == 'D') {
            delta = delta + 1;
        }
    }
}

cv::Mat lac_src,lac_res;
cv::String lacWindowName = "Lapiacian Demo";
TEST(TEST_IMGAE_GRADIENT,test_lapiacian_operator){
    lac_src = cv::imread("rgb/2.png", cv::IMREAD_COLOR);
    if (!lac_src.data) {
        std::cout << "Open Image Error." << std::endl;
        return;
    }
    cv::Mat lap_gray;
    cv::cvtColor(lac_src, lap_gray, cv::COLOR_RGB2GRAY);
    cv::Mat lap_grad_x,lap_grad_y,abs_lap_grad_x,abs_lap_grad_y;
    cv::Laplacian(lap_gray, lac_res, -1, 1, 1, 0);
    cv::convertScaleAbs(lac_res, lac_res);
    cv::namedWindow(lacWindowName, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(lacWindowName, -600, 500);
    cv::imshow(lacWindowName, lac_res);
    cv::waitKey(0);
    }
