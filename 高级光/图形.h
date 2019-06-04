#pragma once
#include <cflw数学.h>
#include <cflw数学_向量.h>
#include <cflw数学_图形.h>
#include <cflw数学_矩阵.h>
#include <cflw图形_d3d11.h>
namespace 数学 = cflw::数学;
namespace 三维 = cflw::图形::d3d11;
class C图形 {
public:
	struct S常量数据 {
		数学::S矩阵4 m世界;
		数学::S矩阵4 m视图;
		数学::S矩阵4 m投影;
	};
	struct S光照数据 {
		数学::S向量4 m光方向;
		数学::S颜色 m光颜色;
	};
	void f初始化(HWND);
	void f销毁();
	void f计算();
	void f更新();
	void f显示();
	三维::C三维 m三维;
	三维::tp顶点着色器 m着色器v;
	三维::tp像素着色器 m着色器p;
	三维::tp缓冲 m常量缓冲, m光照缓冲;
	数学::S世界矩阵3 m世界;
	S常量数据 m常量数据;
	S光照数据 m光照数据;
	数学::S向量2 m窗口大小;
};