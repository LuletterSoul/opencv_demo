//
// Created by LuLetterU on 2018/11/4.
//
#include <opencv2/opencv.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MacTypes.h>

using testing::Eq;

void displayWindows(std::vector<cv::Mat>& frames)
{
    // iterate through the frames
    for(int index = 0; index < frames.size(); ++index)
    {
        // index allows us to assign a unique name to each window
        // windows will be titled 'Window 0', 'Window 1', 'Window 2'... until frames.size()-1
        cv::String windowTitle = "Window " + index;
        imshow(windowTitle, frames[index]);
    }
}
cv::Mat combineImages(std::vector<cv::Mat> imgs,//@parameter1:需要显示的图像组
                  int col,//parameter2:显示的列数
                  int row, //parameter3:显示的行数
                  bool hasMargin){//parameter4:是否设置边框
    int imgAmount = imgs.size();//获取需要显示的图像数量
    int width = imgs[0].cols;//本函数默认需要显示的图像大小相同
    int height = imgs[0].rows;//获取图像宽高
    int newWidth, newHeight;//新图像宽高
    if (!hasMargin){
        newWidth = col*imgs[0].cols;//无边框，新图像宽/高=原图像宽/高*列/行数
        newHeight = row*imgs[0].rows;
    }
    else{
        newWidth = (col + 1) * 20 + col*width;//有边框，要将上边框的尺寸，这里设置边框为20px
        newHeight = (row + 1) * 20 + row*height;
    }
    std::cout << "Image channels :" << imgs[0].channels() << std::endl;
    cv::Mat newImage(newHeight, newWidth, CV_8UC3, cv::Scalar(255, 255, 255));//显示创建设定尺寸的新的大图像；色深八位三通道；填充为白色


    int x, y,imgCount;//x列号，y行号，imgCount图片序号
    if (hasMargin){//有边框
        imgCount = 0;
        x = 0; y = 0;
        while (imgCount < imgAmount){
            cv::Mat imageROI = newImage(cv::Rect(x*width + (x + 1) * 20, y*height + (y + 1) * 20, width, height));//创建感兴趣区域
            imgs[imgCount].copyTo(imageROI);//将图像复制到大图中
            imgCount++;
            if (x == (col - 1)){
                x = 0;
                y++;
            }
            else{
                x++;
            }//移动行列号到下一个位置
        }
    }
    else{//无边框
        imgCount = 0;
        x = 0; y = 0;
        while (imgCount < imgAmount){
            cv::Mat imageROI = newImage(cv::Rect(x*width, y*height, width, height));
            imgs[imgCount].copyTo(imageROI);
            imgCount++;
            if (x == (col - 1)){
                x = 0;
                y++;
            }
            else{
                x++;
            }
        }
    }
    return newImage;//返回新的组合图像
};

TEST(PointTest,point_test){
    cv::Point2i p1(100, 100), p2(102, 103);
    float  res =  p1.dot(p2);
}


TEST(PointConvert, convert_test) {
    cv::Point intPoint(1, 2);
    cv::Point2f floatPoint(2.5, 1.5);
    cv::Point p = floatPoint;
    ASSERT_EQ(p.x,2);
    ASSERT_EQ(p.y,1);
}

TEST(RectTester_TestName_Test, test_rect) {
    cv::Rect r1(100, 100, 102, 103);
    cv::Rect r2(100, 101, 103, 105);
    std::cout << "Rect area is "<<r1.area()<<std::endl;
    std::cout << "Rect multipy area is "<<r1.area()<< r1.area()<<std::endl;
}
void displayImage(cv::Mat &src,cv::String  windowsName,int windowsSize){
    if(windowsSize!=0){
        cv::namedWindow(windowsName, windowsSize);
    }
    else{
        cv::namedWindow(windowsName, 0);
    }
  //  cv::namedWindow(windowsName, windowsSize);
    cv::imshow(windowsName, src);
   // cv::waitKey(0);
   //cv::destroyWindow(windowsName);
}
void houghTransformation(){
    std::vector<cv::Mat> multipleImges, simpleChannelImg;
    std::vector<cv::Mat> displayImages;
    cv::Mat img = cv::imread("/Users/luletteru/CLionProjects/opencv_demo/press/IMG_7586.JPG");
    if(!img.data){
        std::cout<<"Empty Image."<<std::endl;
    }
    else{
        cv::Mat resized_img;
        cv::Mat blurred;
        cv::Mat gray, edges,circles;
        cv::resize(img, resized_img,cv::Size(), 0.15, 0.15, cv::INTER_LINEAR);
       // displayImage(resized_img, "ResizeImg", cv::WINDOW_NORMAL);
        cv::GaussianBlur(resized_img, blurred, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
        cv::cvtColor(blurred, gray, cv::COLOR_BGR2GRAY);
        cv::Canny(resized_img, edges, 50, 150);
        multipleImges.push_back(resized_img);
        multipleImges.push_back(blurred);
        simpleChannelImg.push_back(gray);
        simpleChannelImg.push_back(edges);
        //displayImage(edges, "CannyEdgeEx", cv::WINDOW_NORMAL);
        cv::Mat combinedImge = combineImages(multipleImges, 2, 2, true);
        cv::Mat singleImg = combineImages(simpleChannelImg,  2, 2, true);
        displayImages.push_back(combinedImge);
        displayImages.push_back(gray);
        displayImages.push_back(edges);
        displayWindows(displayImages);
        if (cv::waitKey() == 27) {
            cv::destroyAllWindows();
        }
        //cv::circle()
        ////cv::GaussianBlur(img, blurred, cv::Size(3, 3), 0.2, 0.2, cv::BORDER_DEFAULT);
        ////cv::imshow("GaussianBlurred", blurred);
        ////cv::waitKey(0);
    }

}

TEST(test_hough,test_hought){
    houghTransformation();
}

TEST(test_pydown,pyrdown){
    cv::Mat img = cv::imread("press/IMG_7587.JPG");
    if(!img.data){
        std::cout << "Empty Image." << std::endl;
    }
    cv::Mat pyrdown1, pyrdown2;
    cv::pyrDown(img, pyrdown1);
    cv::pyrDown(pyrdown1, pyrdown2);
    //cv::imshow("PyrdownTest1", pyrdown1);
    cv::imshow("PyrdownTest2", pyrdown2);
    //cv::imshow("ImagePyrdownBefore", ellipse);
    if (cv::waitKey() == 27) {
        cv::destroyAllWindows();
    }
    int x = 16,y=32;
    cv::Vec3b intentity = img.at<cv::Vec3b>(y, x);

    uchar blue = intentity[0];
    uchar green = intentity[1];
    uchar red = intentity[2];

    std::cout << "At (x,y) = (" << x << ", " << y << "): (blue,green,red) is (" << (unsigned int) blue << ", "
              << (unsigned int) green << ", " << (unsigned int) red << ")" << std::endl;
}
