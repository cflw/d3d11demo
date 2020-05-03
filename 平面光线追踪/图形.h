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
	三维::tp缓冲 m常量缓冲0, m常量缓冲1, m顶点缓冲;
	三维::tp图形管线 m圆管线, m光管线;
	S顶点 m顶点数据[c总顶点数];
	C粒子管理 m粒子管理;
	struct S窗口常量 {
		数学::S向量2 m窗口大小;
	} m窗口常量;
	S圆常量 m圆常量[c圆数量];
};