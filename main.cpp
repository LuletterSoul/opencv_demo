#include <iostream>
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

//int main() {
//    cv::Mat ellipse = cv::imread("/usr/local/opencv/images/Images/DIP3E_Original_Images_CH03/Fig0359(a)(headCT_Vandy).tif");
//    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
//    if(!ellipse.data){
//        std::cout<<"Empty image"<<std::endl;
//        return -1;
//    }
//    else{
//        cv::imshow("Example1", ellipse);
//        cv::waitKey(0);
//        cv::destroyWindow("Example1");
//    }
//    return 0;
int main(int argc, char *argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



