#pragma once
#include <cflw数学.h>
#include <cflw图形_d3d11.h>
#include "粒子.h"
namespace 数学 = cflw::数学;
namespace 三维 = cflw::图形::d3d11;
class C图形 {
public:
	void f初始化(HWND);
	void f销毁();
	void f计算();
	void f更新();
	void f显示();
	三维::C三维 m三维;
	三维::tp顶点着色器 m着色器v;
	三维::tp几何着色器 m着色器g;
	三维::tp像素着色器 m着色器p;
	struct S常量 {
		数学::S向量2 m窗口大小;
		float m粒子大小;
	} m常量;
	三维::tp缓冲 m顶点缓冲;
	S粒子 ma粒子数据[c粒子数量] = {};
	C粒子 ma粒子对象[c粒子数量] = {};
};