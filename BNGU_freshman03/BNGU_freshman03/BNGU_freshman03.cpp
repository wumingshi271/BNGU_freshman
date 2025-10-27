#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // 打开摄像头
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "无法打开摄像头" << endl;
        return -1;
    }
    Mat frame, result, gray, thresh;
    while (true)
    {
        // 读取摄像头帧
        cap >> frame;
        if (frame.empty()) {
            cout << "无法获取帧！" << endl;
            return -1;
        }
        result = frame.clone();  // 复制帧用于绘制结果

        // 获取 HSV 色彩空间
        Mat capH, capS, capV;
        cvtColor(frame, frame, COLOR_BGR2HSV);
        vector<Mat> hsvPlanes;
        split(frame, hsvPlanes);
        capH = hsvPlanes[0];
        capS = hsvPlanes[1];
        capV = hsvPlanes[2];

        // 筛选黑色
        Mat mask, maskH, maskS, maskV;
        inRange(capH, 0, 180, maskH);  // 色调不限
        inRange(capS, 0, 255, maskS);  // 饱和度不限
        inRange(capV, 0, 30, maskV);   // 亮度低于一定值

        // 合并掩码
        bitwise_and(maskH, maskS, mask);
        bitwise_and(mask, maskV, mask);

        // 应用掩码提取黑色区域
        Mat frameOut;
        bitwise_and(frame, frame, frameOut, mask);

        // 提取灰度图像
        Mat gray;
        cvtColor(frameOut, gray, COLOR_BGR2GRAY);

        // 去除噪点， 使轮廓更加完整
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        Mat thresh;
        erode(gray, thresh, kernel);
        dilate(thresh, thresh, kernel);

        // 查找轮廓
        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // 遍历轮廓，处理椭圆
        for (const auto& contour : contours) {
            // 过滤面积过小的轮廓
            double area = contourArea(contour);
            if (area < 15000)
            {
                continue;
            }

            // 计算轮廓周长,过滤短的轮廓
            double perimeter = arcLength(contour, true);
            if (perimeter < 200)
            {
                continue;
            }

            // 高精度多边形拟合
            vector<Point> approx;
            double epsilon = 0.005 * perimeter;  // 拟合精度：值越小越接近椭圆
            approxPolyDP(contour, approx, epsilon, true);

            // 椭圆拟合至少需要5个顶点
            if (approx.size() < 6)
            {
                continue;
            }


            // 计算外接矩形
            Rect rect = boundingRect(approx);
            // 绘制矩形
            rectangle(result, rect, Scalar(0, 255, 0), 2);
        }



        // 显示结果
        imshow("result", result);

        // 按q退出
        char key = waitKey(1);
        if (key == 'q')
        {
            break;
        }
    }

    // 释放资源
    cap.release();
    destroyAllWindows();
    return 0;
}
