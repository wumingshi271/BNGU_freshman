#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main() {
    // 读取图片
    Mat img = imread("bed_pic.png");
    if (img.empty()) {
        printf("无法读取图片！\n");
        return -1;
    }
    // 转换为 HSV 色彩空间
    Mat img_hsv;
    cvtColor(img, img_hsv, COLOR_BGR2HSV);  

    // 分离 HSV 三个通道
    Mat img_h, img_s, img_v;
    vector<Mat> channels;
    split(img_hsv, channels);
	channels[0].copyTo(img_h);  
	channels[1].copyTo(img_s);  
	channels[2].copyTo(img_v);  

    // 阈值化处理，提取粉色
    Mat mask_h, mask_s, mask_v;
    inRange(img_h, 150, 200, mask_h);  // H 通道阈值：粉色范围
    inRange(img_s, 0, 255, mask_s);    // S 通道不限制（0-255）
    inRange(img_v, 0, 255, mask_v);    // V 通道不限制（0-255）

    // 对三个通道的掩码进行与操作（获取同时满足三个条件的区域）
    Mat mask_h_and_s, mask;
    bitwise_and(mask_h, mask_s, mask_h_and_s);  // H & S
    bitwise_and(mask_h_and_s, mask_v, mask);    // (H&S) & V

    // 应用掩码提取原图中的粉色区域
    Mat img_out;
    bitwise_and(img, img, img_out, mask);  // 用 mask 筛选原图

    // 显示结果图像
    imshow("粉色提取结果", img_out);

    // 保存结果图像
    bool saveSuccess = imwrite("img_out.png", img_out);
    if (!saveSuccess) {
        cerr << "保存图像失败！" << endl;
    }


    // 等待按键（0 表示无限等待）
    waitKey(0);
    destroyAllWindows();  // 关闭所有窗口
}