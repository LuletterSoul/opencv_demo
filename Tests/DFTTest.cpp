//
// Created by LuLetterU on 2018/11/16.
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


TEST(DFT_TESt,test_dft_and_show_magnutitue){
    cv::Mat img = cv::imread("rgb/1.jpg",cv::IMREAD_GRAYSCALE);

    if (img.empty()) {
        std::cout << "Error opening image.Image is empty." << std::endl;
        return;
    }
    cv::Mat padded;
    int padRows = cv::getOptimalDFTSize(img.rows);
    int padCols = cv::getOptimalDFTSize(img.cols);
    cv::copyMakeBorder(img, padded, 0 , padRows - img.rows, 0, padCols - img.cols,
                       cv::BORDER_CONSTANT, cv::Scalar::all(0));

    cv::Mat planes [] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
    cv::Mat complexI;
    cv::merge(planes, 2,complexI);

    cv::dft(complexI, complexI);
    cv::split(complexI, planes);
    cv::magnitude(planes[0], planes[1], planes[0]);
    cv::Mat magI = planes[0];
    magI += cv::Scalar::all(1);

    cv::log(magI, magI);

    magI  = magI(cv::Rect(0, 0, magI.cols& -2, magI.rows& -2));
    cv::Mat spectrumImage;

    magI.copyTo(spectrumImage);

    cv::normalize(magI, spectrumImage, 0, 1, cv::NORM_MINMAX);
    cv::imshow("Spectrum of Image:", spectrumImage);


    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy));

    cv::Mat tmp ;

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);

    cv::imshow("Spectrum Magnitude", magI);
    cv::imshow("Orignal Image", img);
    cv::waitKey(0);
}
