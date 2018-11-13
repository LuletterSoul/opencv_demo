//
// Created by LuLetterU on 2018/11/4.
//
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::Eq;

TEST(MatTest,mat_create_test){
    cv::Mat m = cv::Mat::ones(10, 10, CV_32FC3);
    printf("Element (3,3,3) is (%f,%f,%f)\n", m.at<cv::Vec2f>(3, 3)[0], m.at<cv::Vec2f>(3, 3)[1],
           m.at<cv::Vec2f>(3,3)[2]);
}


TEST(MatTest,mat_ramdom_mat_display){
    cv::Mat n_mat = cv::Mat::ones(1024, 1024, CV_32FC3);
    cv::randu(n_mat, 0.0f, 255.0f);
    cv::namedWindow("randu_img", CV_WINDOW_AUTOSIZE);
    cv::imshow("randu_img", n_mat);
    cv::waitKey(0);
    cv::destroyWindow("randu_img");
}

TEST(MatTest,mat_compute_longest_vector_3d){
    int sz[3] = {4,4,4};
    cv::Mat m(3, sz, CV_32FC3);
    cv::randu(m, -1.0f, 1.0f);

    float max = 0.0f,len = 0.0f;
    cv::MatConstIterator_<cv::Vec3f> it = m.begin<cv::Vec3f>();
    while (it != m.end<cv::Vec3f>()) {
        for (int i = 0; i < 3; i++) {
            len += (*it)[i]+(*it)[i];
        }
        if (len > max) {
            max = len;
        }
        it ++;
    }
    printf("Max len of 3-d matrix is %f", max);
}

TEST(MatTest,test_mat_creation){
    int sz[3] = {3, 3, 3};


}

