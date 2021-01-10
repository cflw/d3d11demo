# Direct3D 11演示
这是为了测试[乘风龙王的代码库(c++)](https://github.com/cflw/cflw_cpp)的**cflw图形_d3d11**是否可用而写的代码。


项目依赖项：
* [乘风龙王的代码库(c++)](https://github.com/cflw/cflw_cpp)

## 内容包含
我把有的没的想要做的都列出来了，没有的以后补上。

### 基础

* **空白窗口**：创建一个窗口并初始化d3d11设备。同时作为下面代码的模板。
* **简单三角形**：使用顶点着色器和像素着色器画一个三角形
* **简单立方体**：画一个不断旋转的立方体
* **简单二维**：纯Direct3D 11绘制二维图形。
* **二维文本**：与Direct2D混合渲染。

### 基础+

* **纹理立方体**：画一个带纹理、不断旋转的立方体。纹理和模型来自外部文件。
* **简单光**：离光远的像素暗。
* **简单雾**：离镜头远的像素暗。
* **深度模板**：不同深度的三角形放在一起，前面遮住后面，中间放一个圆形遮罩。
* **粒子**：使用几何着色器画粒子。
* **天空盒**：使用一个带有六张纹理图片的立方体组成一个天空场景

### 进阶

* **高级光**：用不同的光画出立方体表面。
* **光影**：画物体阴影
* **边框**：使用几何着色器画物体边缘
* **曲面细分**：曲面细分代码模板，观察正方形细分结果。
* **分辨率与全屏**：调整分辨率和全屏状态。按`←`、`→`调分辨率，按`ALT`+`ENTER`切换全屏。
	* **注意**：对于有多显卡的电脑（特别是笔记本电脑），全屏可能失败。因为`cflw::图形::d3d11::C创建设备::f取显卡`总是选择性能最高的显卡进行渲染，当渲染显卡与输出显卡不一致会导致设置全屏失败。
	* N卡的解决方法：在**NVIDIA控制面板->管理3D设置->首选图形处理器**选择**高性能NVIDIA处理器**可以解决此问题。
* **天空球**：使用一个带有六张纹理图片的球体组成一个天空场景

### 进阶+

* **曲面细分2**：使用外壳着色器和域着色器画光滑曲面。
* **平面光线追踪**：使用像素着色器计算光线。多个聚光灯叠加照射，不断移动的圆形反复遮挡光线，呈现出复杂阴影。
* **镜面反射**：一面镜子反射一个立方体

### 高级&特效

*没想好要做什么*