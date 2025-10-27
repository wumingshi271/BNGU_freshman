#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main() {
    // 读取图片
    Mat img = imread("bed_pic.png");
    if (img.empty()) {
        cout << "无法读取图片！" << endl;
        return -1;
    }

    // 转换为 HSV 色彩空间
    Mat imgHsv;
    cvtColor(img, imgHsv, COLOR_BGR2HSV);  

    // 分离 HSV 三个通道
    Mat imgH, imgS, imgV;
    vector<Mat> channels;
    split(imgHsv, channels);
	channels[0].copyTo(imgH);  
	channels[1].copyTo(imgS);  
	channels[2].copyTo(imgV);  

    // 阈值化处理，提取粉色
    Mat maskH, maskS, maskV;
    inRange(imgH, 150, 200, maskH);  // H 通道阈值：粉色范围
    inRange(imgS, 0, 255, maskS);    // S 通道不限制（0-255）
    inRange(imgV, 0, 255, maskV);    // V 通道不限制（0-255）

    // 对三个通道的掩码进行与操作（获取同时满足三个条件的区域）
    Mat mask_h_and_s, mask;
    bitwise_and(maskH, maskS, mask_h_and_s);  // H & S
    bitwise_and(mask_h_and_s, maskV, mask);    // (H&S) & V

    // 应用掩码提取原图中的粉色区域
    Mat imgOut;
    bitwise_and(img, img, imgOut, mask);  // 用 mask 筛选原图

    // 显示结果图像
    imshow("粉色提取结果", imgOut);

    // 保存结果图像
    bool saveSuccess = imwrite("imgOut.png", imgOut);
    if (!saveSuccess) {
        cerr << "保存图像失败！" << endl;
    }


    // 等待按键
    waitKey(0);
    destroyAllWindows();  // 关闭所有窗口
}