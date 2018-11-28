//
// Created by LuLetterU on 2018/11/19.
//
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#define WIN_LOCATION_X -600
#define WIN_LOCATION_Y 500
int open_type = 0,open_kernel_size = 0, open_kernel_max_size = 8;
int close_type = 0,close_kernel_size = 0,close_kerel_max_size = 8;
cv::Mat op_src,opening_res,gradient_src,gradient_res,top_hat_operate_src,back_hat_operate;
cv::Mat closing_res,top_hat_res,black_hat_res;
cv::String openWinName= "Open Demo";
cv::String closeWinName = "Close Demo";
static void Open(int ,void *);

static void Close(int, void *);

static void Open(int i,void * func){
cv::Mat structuring_ele = cv::getStructuringElement(open_type, cv::Size(open_kernel_size* 2 + 1,
                                                                             open_kernel_size* 2 + 1),
                                                        cv::Point(open_kernel_size, open_kernel_size));
    cv::morphologyEx(op_src, opening_res, cv::MORPH_OPEN, structuring_ele, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT,
                     cv::morphologyDefaultBorderValue());
    cv::morphologyEx(opening_res, opening_res, cv::MORPH_CLOSE, structuring_ele, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT,
                     cv::morphologyDefaultBorderValue());
    cv::imshow(openWinName, opening_res);
}
static void Close(int i , void *func){
    cv::Mat structuring_ele = cv::getStructuringElement(close_type, cv::Size(close_kernel_size * 2 + 1,
                                                                             close_kerel_max_size * 2 + 1),
                                                        cv::Point(close_kerel_max_size, close_kernel_size));
    cv::morphologyEx(op_src, opening_res, cv::MORPH_OPEN, structuring_ele, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT,
                     cv::morphologyDefaultBorderValue());
    cv::imshow(openWinName, opening_res);
}
TEST(MORPH_TRANS_TEST,test_open_and_close_tranformation){
    op_src = cv::imread("dip/char_9/Fig0938(a)(cygnusloop_Xray_original).tif");
    open_type = cv::MORPH_ELLIPSE;
    close_type = cv::MORPH_ELLIPSE;
    cv::imshow(openWinName, op_src);
    cv::moveWindow(openWinName, WIN_LOCATION_X, WIN_LOCATION_Y);
    cv::createTrackbar("Kernel Size:", openWinName, &open_kernel_size, open_kernel_max_size, Open);
    //cv::createTrackbar("Closing Kernel Size:", closeWinName, &close_kernel_size, close_kerel_max_size, Close);
    cv::waitKey(0);
}
TEST(MORPH_TRANS_TEST,test_do_gradient_edge_detection){
    gradient_src = cv::imread("dip/char_9/Fig0939(a)(headCT-Vandy).tif", cv::IMREAD_GRAYSCALE);
    cv::String gradientWindowName = "Morphological Gradient Demo";
    cv::String erodeWindowName = "Erode of HeadCT-Vandy";
    cv::String dilationWindowName= "Dilation of HeadCT-Vandy";
    cv::namedWindow(gradientWindowName, CV_WINDOW_AUTOSIZE);
    cv::Mat structureEle = cv::Mat::ones(cv::Size(3, 3), CV_8U);
    cv::Mat openAndCloseStructureEle= cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3), cv::Point(-1, -1));
    cv::morphologyEx(gradient_src, gradient_res, cv::MORPH_ERODE, openAndCloseStructureEle);
    cv::imshow(erodeWindowName, gradient_res);
    cv::moveWindow(erodeWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);

    cv::morphologyEx(gradient_src, gradient_res, cv::MORPH_DILATE, structureEle);
    cv::imshow(dilationWindowName, gradient_res);
    cv::moveWindow(dilationWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);

    cv::morphologyEx(gradient_src, gradient_res, cv::MORPH_GRADIENT, structureEle);
    cv::imshow(gradientWindowName,gradient_res);
    cv::moveWindow(gradientWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);
    cv::waitKey(0);
}

int threshold_max = 255,threshold_value =0;
int kernel_size = 0 ,max_kernel_size = 10;
int rice_structure_ele_type = 0;
cv::Mat rice_src,rice_res;
cv::String riceWindowName = "Rice With Intensity and Gradient Demo.";
cv::String riceThresholdedWindowName = "Rice with thresholded Image Demo";
cv::String openingRiceWindowName = "Rice with opening Image Demo";
cv::String topHatWindowName = "Rice with Top Hat Trans Demo";
cv::String topHatAndThresholdWindowName = "Rice with Top Hat And Threshold Demo";

static void onThresholdBarChange(int, void *);

//when the threshold bar on touched,the cv::threshold function will be executed.
static void onThresholdBarChange(int i, void *func){
    //THRESH_BINARY means that the pixel intensity set to 0 when it is less than threshold_value,otherwise,set to the threshold_max;
    cv::threshold(top_hat_operate_src, top_hat_res, threshold_value, threshold_max, cv::THRESH_BINARY);
    cv::imshow(riceThresholdedWindowName, top_hat_res);
    cv::imshow(topHatAndThresholdWindowName, top_hat_res);
}


TEST(MORPH_TRANS_TEST,test_top_hat_operation){
    top_hat_operate_src = cv::imread("dip/char_9/Fig0940(a)(rice_image_with_intensity_gradient).tif");
    top_hat_res = top_hat_operate_src.clone();
    if (!top_hat_operate_src.data) {
        std::cout << "Opened Image Error."<<std::endl;
        return;
    }
    cv::namedWindow(riceWindowName, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(riceThresholdedWindowName, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(openingRiceWindowName, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(topHatWindowName, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(topHatAndThresholdWindowName, cv::WINDOW_AUTOSIZE);
    //show original image
    cv::imshow(riceWindowName, top_hat_operate_src);
    cv::moveWindow(riceWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);

    //create a configurable threshold bar to the threshold image
    cv::createTrackbar("ThresholdBar:", riceThresholdedWindowName, &threshold_value, threshold_max,
                       onThresholdBarChange);
    cv::imshow(riceThresholdedWindowName, top_hat_res);
    cv::moveWindow(riceThresholdedWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);


    //do a morphological opening transformation using 40 * 40 size structure element.
    cv::Mat open_el = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(40, 40));
    cv::morphologyEx(top_hat_operate_src, top_hat_res, cv::MORPH_OPEN, open_el);
    cv::imshow(openingRiceWindowName, top_hat_res);
    cv::moveWindow(openingRiceWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);

    cv::Mat top_hat_el = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(40, 40));
    cv::createTrackbar("ThresholdBar", topHatAndThresholdWindowName, &threshold_value, threshold_max, onThresholdBarChange);
    cv::morphologyEx(top_hat_operate_src, top_hat_operate_src, cv::MORPH_TOPHAT, top_hat_el);
    top_hat_res = top_hat_operate_src.clone();
    cv::imshow(topHatAndThresholdWindowName, top_hat_res);
    cv::moveWindow(topHatAndThresholdWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);
    cv::waitKey(0);
    }

cv::Mat wood_src,wood_res;
cv::String woodWindowName = "Wood Smoothing Demo";
int wood_structure_ele_size = 0, wood_structure_max_size = 30;


static void onWoodTraceBarChange(int, void *);

static void onWoodTraceBarChange(int i, void *func){
    cv::Mat ele = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                            cv::Size(wood_structure_ele_size * 2 + 1, wood_structure_ele_size * 2 + 1),
                                            cv::Point(wood_structure_ele_size, wood_structure_ele_size));
    cv::morphologyEx(wood_src, wood_res, cv::MORPH_OPEN, ele);
    cv::Scalar sum = cv::sum(wood_res);
    std::cout << sum << std::endl;
    cv::imshow(woodWindowName, wood_res);
}

void caculateDiffVecInOpeningProcessing(std::vector<cv::Scalar> &surfaceAreas){
    for (int i = 0; i < wood_structure_max_size; ++i) {
        cv::Mat ele = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(i * 2 + 1, i * 2 + 1), cv::Point(i, i));
        cv::morphologyEx(wood_src, wood_res, cv::MORPH_OPEN, ele);
        surfaceAreas.push_back(cv::sum(wood_res));
    }
}

TEST(MORPH_TRANS_TEST,test_filter_woods){
    wood_src = cv::imread("dip/char_9/Fig0941(a)(wood_dowels).tif", cv::IMREAD_GRAYSCALE);
    wood_res = wood_src.clone();
    if (!wood_src.data) {
        std::cout << "Open Image Error." << std::endl;
        return;
    }
    std::vector<cv::Scalar> surfaceArea;
    cv::namedWindow(woodWindowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(woodWindowName, wood_src);
    cv::moveWindow(woodWindowName, WIN_LOCATION_X, WIN_LOCATION_Y);
    caculateDiffVecInOpeningProcessing(surfaceArea);
    cv::createTrackbar("Kernel Size:", woodWindowName, &wood_structure_ele_size, wood_structure_max_size,
                       onWoodTraceBarChange);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
