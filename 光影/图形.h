#pragma once
#include <cflw数学.h>
#include <cflw数学_向量.h>
#include <cflw数学_图形.h>
#include <cflw数学_矩阵.h>
#include <cflw数学_立体几何.h>
#include <cflw图形_d3d11.h>
namespace 数学 = cflw::数学;
namespace 三维 = cflw::图形::d3d11;
class C图形 {
public:
	struct S物体顶点 {
		数学::S向量3 m坐标;
		数学::S向量3 m法线;
		数学::S向量2 m纹理;
	};
	struct S固体顶点 {
		数学::S向量3 m坐标;
		数学::S颜色 m颜色;
	};
	struct S矩阵数据 {
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
	三维::tp顶点着色器 m物体v, m固体v;
	三维::tp像素着色器 m物体p, m固体p, m阴影p;
	三维::tp缓冲 m矩阵常量, m光照常量, m立方体顶点, m平面顶点, m平面索引;
	三维::tp输入布局 m物体布局, m固体布局;
	数学::S世界矩阵3 m物体;
	S矩阵数据 m矩阵数据;
	S光照数据 m光照数据;
	数学::S平面3 m阴影平面;
	数学::S向量2 m窗口大小;
	float m时间 = 0;
};