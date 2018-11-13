//
// Created by LuLetterU on 2018/11/13.
//
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


cv::Mat &scanImgAndReduceImgColor(cv::Mat &img, const uchar *table){
    int rows = img.rows;
    int cols = img.cols * img.channels();


    uchar * p ;

    if (img.isContinuous()) {
        cols *= rows;
        rows = 1;
    }
    for (int i = 0; i < rows; ++i) {
        p = img.ptr<uchar>(i);
        for (int j = 0; j < cols; ++j) {
            p[j] = table[p[j]];
        }
    }
    return img;
}

void getTable(uchar *table, int divideWidth){
    for (int i = 0; i < 256; ++i) {
        table[i] = static_cast<uchar>((i / divideWidth) * divideWidth);
    }
}

TEST(COLOR_REDUCTION_TEST,test_reduce_color_16_million_by_divideWidth){
    cv::Mat img = cv::imread("rgb/1.jpg");
    std::cout << "Image Size is (" << img.rows << ","<< img.cols << ")" << std::endl;
    std::cout << "Image Channels:" << img.channels() << std::endl;
    uchar *table = new uchar[256];
    if (img.data == NULL) {
        std::cout << "Empty Image." << std::endl;
        return;
    }
    cv::imshow("BeforeReductionImage", img);
    getTable(table, 15);
    cv::Mat afterReductionImg = scanImgAndReduceImgColor(img, table);
    cv::imshow("AfterReductionImage", afterReductionImg);
    cv::waitKey(0);
}
