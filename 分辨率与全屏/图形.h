#pragma once
#include <cflw数学.h>
#include <cflw图形_d3d11.h>
namespace 数学 = cflw::数学;
namespace 三维 = cflw::图形::d3d11;
class C图形 {
public:
	struct S顶点 {
		数学::S向量2 m坐标;
		数学::S颜色 m颜色;
	};
	void f初始化(HWND);
	void f重置();
	void f销毁();
	void f计算();
	void f更新();
	void f显示();
	void fs全屏(bool);
	void fs窗口大小(int, int);
	三维::C三维 m三维;
	三维::tp顶点着色器 m着色器v;
	三维::tp像素着色器 m着色器p;
	三维::tp输入布局 m输入布局;
	三维::tp缓冲 m顶点;
};