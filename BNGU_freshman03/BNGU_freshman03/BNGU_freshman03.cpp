#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    //  打开摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "无法打开摄像头！" << endl;
        return -1;
    }


    Mat frame, result, gray, thresh;
    while (true) {
        // 读取摄像头帧
        cap >> frame;
        if (frame.empty()) {
            cerr << "无法获取帧！" << endl;
            break;
        }
        result = frame.clone();  // 复制帧用于绘制结果

        // 获取 HSV 色彩空间
		Mat cap_h,cap_s,cap_v;
		cvtColor(frame, frame, COLOR_BGR2HSV);
		vector<Mat> hsv_planes;
		split(frame, hsv_planes);
		cap_h = hsv_planes[0];
		cap_s = hsv_planes[1];
		cap_v = hsv_planes[2];

        // 筛选黑色
		Mat mask, mask_h, mask_s, mask_v;
		inRange(cap_h, 0, 180, mask_h);  // 色调不限
		inRange(cap_s, 0, 255, mask_s);  // 饱和度不限
		inRange(cap_v, 0, 30, mask_v);   // 亮度低于一定值

        // 合并掩码
        bitwise_and(mask_h, mask_s, mask);
        bitwise_and(mask, mask_v, mask);

		// 应用掩码提取黑色区域
        Mat frame_out;
        bitwise_and(frame, frame, frame_out, mask);

        // 提取灰度图像
        Mat gray;
        cvtColor(frame_out, gray, COLOR_BGR2GRAY);

        // 去除噪点， 使轮廓更加完整
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        Mat thresh;
        erode(gray, thresh, kernel);
        dilate(thresh, thresh, kernel);

        // 查找轮廓
        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // 遍历轮廓，处理椭圆
        for (size_t i = 0; i < contours.size(); i++) {
            // 过滤面积过小的轮廓（排除噪点，可根据实际场景调整）
            double area = contourArea(contours[i]);
            if (area < 15000) continue;  // 面积阈值：避免过小的干扰目标

            // 计算轮廓周长
            double perimeter = arcLength(contours[i], true);
            if (perimeter < 200) continue;  // 周长阈值：过滤短轮廓

            // 高精度多边形拟合
            vector<Point> approx;
            double epsilon = 0.005 * perimeter;  // 拟合精度：值越小越接近椭圆
            approxPolyDP(contours[i], approx, epsilon, true);

            // 椭圆拟合至少需要5个顶点（排除直线/矩形等）
            if (approx.size() < 6) continue;

            // 计算外接矩形
            Rect rect = boundingRect(approx);
            // 绘制矩形
            rectangle(result, rect, Scalar(0, 255, 0), 2);
        }

        // 显示结果
        imshow("椭圆检测与拟合（摄像头）", result);

        // 按 'q' 键退出
        char key = waitKey(1);
        if (key == 'q' || key == 27) {  // 27是ESC键
            break;
        }
    }

    // 释放资源
    cap.release();
    destroyAllWindows();
    return 0;
}
