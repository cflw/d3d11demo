#pragma once
#include <cflw数学.h>
#include <cflw数学_平面几何.h>
#include <cflw图形_d3d11.h>
namespace 数学 = cflw::数学;
namespace 三维 = cflw::图形::d3d11;
class C画图形;
struct S顶点 {
	数学::S向量2 m坐标;
	数学::S颜色 m颜色;
};
class C二维 {
public:
	class C资源管理;
	//函数
	C二维();
	~C二维();
	void f初始化(三维::C三维 &);
	void f开始();
	void f结束();
	std::shared_ptr<C画图形> fc画图形();
	C资源管理 &fg资源管理();
public:
	三维::C三维 *m三维 = nullptr;
	std::unique_ptr<C资源管理> m资源管理;
};
class C画图形 {
public:
	C画图形(C二维 &);
	//设置
	void fs线条宽度(float);
	void fs颜色(const 数学::S颜色 &);
	void fs透明度(float);
	//描线
	void f绘制点(const 数学::S向量2 &);
	void f绘制线条(const 数学::S线段2 &);
	void f绘制矩形(const 数学::S矩形 &);
	void f绘制旋转矩形(const 数学::S旋转矩形 &);
	void f绘制圆形(const 数学::S圆形 &);
	void f绘制椭圆(const 数学::S椭圆 &);
	void f绘制圆角矩形(const 数学::S圆角矩形 &);
	//填充
	void f填充矩形(const 数学::S矩形 &);
	void f填充旋转矩形(const 数学::S旋转矩形 &);
	void f填充圆形(const 数学::S圆形 &);
	void f填充椭圆(const 数学::S椭圆 &);
	void f填充圆角矩形(const 数学::S圆角矩形 &);
	void f填充三角形(const 数学::S三角形 &);
public:
	C二维::C资源管理 *m资源管理 = nullptr;
	数学::S颜色 m颜色 = 数学::S颜色::c白;
	float m线条宽度 = 2;
};