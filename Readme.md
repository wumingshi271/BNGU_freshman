# BNGU视觉组考核题

本项目是吴子昂考核题的汇总，整合了Opencv颜色分割、Opencv最小框选与多边形拟合、OpenCV最小框选与多边形拟合（选做题）、OpenCV物体位姿演算与solvePnP实战的题目，并且分别以01、02、03、04的顺序排列

## 一. 项目结构说明

每个题目对应的文件夹里面都有BNGU_freshman**的文件夹，还有演示的视频。

### 1. BNGU_freshman**文件夹

里面有完整的源码可以查看

### 2. 演示视频（格式通常为0*）

顾名思义就是项目的演示视频

## 二. 使用方法

### 编译源代码文件

#### 步骤 1：创建新项目

1. 打开 **Visual Studio**，创建 “控制台项目”（名称如 Test）
2. 右键项目 → 添加 → 新建项 → 选择 “C++ 文件 (.cpp)”，命名为 test.cpp
3. 将项目代码复制到 test.cpp 中

#### 步骤 2：配置 OpenCV 依赖
1. 右键项目 → 属性（或按 Alt+F7）
2. 在 **配置属性 → VC++目录 → 包含目录** 中，添加 OpenCV 的 include 路径：
* 例：D:\opencv\build\include;D:\opencv\build\include\opencv2
3. 在 **配置属性 → VC++目录 → 库目录** 中，添加 OpenCV 的 lib 路径：
* 例：D:\opencv\build\x64\vc15\lib（根据你的 Visual Studio 版本选择 vc14/vc15/vc16）
4. 在 配置属性 → 链接器 → 输入 → 附加依赖项 中，添加 OpenCV 库文件名（根据你的 OpenCV 版本调整，如 4.8.0 版本）：
* **Debug** 模式：opencv_world480d.lib
* **Release** 模式：opencv_world480.lib
* 选择 **平台** 为 **x64（OpenCV 64 位版本）**，配置 为 Debug 或 Release

#### 步骤 3： 配置环境变量
1. 点开电脑上的 **编辑环境变量**
2. 在 **环境变量 → 系统变量 → 新建** 中，输入OpenCV的 **bin** 文件目录
* 例：
* 变量：opencv
* 值：D:\opencv\build\x64\vc16\bin
3. 点击确定并且保存

#### 步骤 4：编译运行
1. 点击 **生成 → 生成解决方案**（或按 **Ctrl+Shift+B**）
2. 编译成功后，点击 **调试 → 开始执行（不调试）（或按 Ctrl+F5）**

### 观看视频的演示效果

该视频由于虚拟机的原因，无法使用电脑的摄像头，因此前两个题目是在 **Ubantu** 下运行的。而后两道题目由于需要使用摄像头，是在 **Windows** 下运行的

## 三. 运行建议

* 准备一个摄像头，并且要测定好它的内参（第四题可以在源码中修改内参）

## 四. 各题目分别的源码仓库（里面有python和C++版本）

### Python

01：颜色分割 							[https://github.com/wumingshi271/BNGU_freshman01](https://github.com/wumingshi271/BNGU_freshman01)


02：最小框选与多边形拟合 				[https://github.com/wumingshi271/BNGU_freshman02](https://github.com/wumingshi271/BNGU_freshman02)


03：最小框选与多边形拟合（选做题）	[https://github.com/wumingshi271/BNGU_freshman03](https://github.com/wumingshi271/BNGU_freshman03)


04：物体位姿演算与solvePnP实战		[https://github.com/wumingshi271/BNGU_freshman_04](https://github.com/wumingshi271/BNGU_freshman_04)

### C++

01：颜色分割 							[https://github.com/wumingshi271/BNGU_freshman01_C-_version](https://github.com/wumingshi271/BNGU_freshman01_C-_version)


02：最小框选与多边形拟合 				[https://github.com/wumingshi271/BNGU_freshman02_C-_version](https://github.com/wumingshi271/BNGU_freshman02_C-_version)


03：最小框选与多边形拟合（选做题）	[https://github.com/wumingshi271/BNGU_freshman03_C-_version](https://github.com/wumingshi271/BNGU_freshman03_C-_version)


04：物体位姿演算与solvePnP实战		[https://github.com/wumingshi271/BNGU_freshman_04_C-_version](https://github.com/wumingshi271/BNGU_freshman_04_C-_version)


## 最后寄语

看在我写Readme这么勤奋的面子上，可以给我一颗小星星吗（；´д｀）ゞ