#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // 读取图片
    Mat img = imread("image.png");
    if (img.empty())
    {
        cout << "无法读取图片" << endl;
        return -1;
    }

    // 转化为hsv色彩空间
    Mat imgH, imgS, imgV;
    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);
    vector<Mat> hsvChannels;
    split(hsv, hsvChannels);
    imgH = hsvChannels[0];
    imgS = hsvChannels[1];
    imgV = hsvChannels[2];

    // 阈值化处理，提取高亮度
    Mat maskH, maskS, maskV;
    inRange(imgH, 0, 255, maskH);
    inRange(imgS, 0, 255, maskS);
    inRange(imgV, 245, 255, maskV);

    // 合并掩码
    Mat mask;
    bitwise_and(maskH, maskS, mask);
    bitwise_and(mask, maskV, mask);
    Mat imgOut;
    bitwise_and(img, img, imgOut, mask);

    // 提取灰度图像
    Mat gray;
    cvtColor(imgOut, gray, COLOR_BGR2GRAY);

    // 形态学处理，消除噪点
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat thresh;
    erode(gray, thresh, kernel);
    dilate(thresh, thresh, kernel);

    // 查找轮廓
    vector<vector<Point> > contours;
    findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 遍历轮廓，查找六边形
    for (const auto& contour : contours)
    {
        // 过滤掉小面积的轮廓
        double area = contourArea(contour);
        if (area < 100)
        {
            continue;
        }

        // 多边形拟合
        vector<Point> approx;
        approxPolyDP(contour, approx, 3, true);

        // 判断是否为六边形
        if (approx.size() == 6)
        {
            // 计算并绘制六边形的外接矩形
            Rect rect = boundingRect(approx);
            rectangle(img, rect, Scalar(0, 255, 0), 2);
        }
    }
    // 显示结果
    imshow("img", img);
    imwrite("result.png", img);
    waitKey(0);
    return 0;

}