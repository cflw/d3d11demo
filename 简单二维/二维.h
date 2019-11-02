#pragma once
#include <cflw数学.h>
#include <cflw数学_平面几何.h>
#include <cflw图形_d3d11.h>
namespace 数学 = cflw::数学;
namespace 三维 = cflw::图形::d3d11;
class C画图形;
class C坐标转换;
class C二维 {
public:
	//常量
	static constexpr int c圆形边数 = 16;
	static constexpr int c圆形顶点数 = c圆形边数;
	static constexpr int c四分圆边数 = c圆形边数 / 4;
	static constexpr int c最大顶点数 = c圆形边数;
	static constexpr uint16_t ca矩形索引[] = {
		0, 1, 2,
		1, 3, 2,
	};
	static constexpr int c矩形索引数 = _countof(ca矩形索引);
	static constexpr int c圆形索引数 = (c圆形边数 - 2) * 3;
	static constexpr int c最大索引数 = c圆形索引数;
	//函数
	void f初始化(三维::C三维 &);
	void f准备();
	std::shared_ptr<C画图形> fc画图形();
public:
	三维::C三维 *m三维 = nullptr;
	struct S资源 {
		三维::tp输入布局 m输入布局;
		三维::tp缓冲 m顶点缓冲, m矩形索引缓冲, m圆形索引缓冲;
		三维::tp顶点着色器 m着色器v;
		三维::tp像素着色器 m着色器p;
		三维::tp缓冲 m顶点常量缓冲, m像素常量缓冲;
	} m资源;
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
public:
	三维::C三维 *m三维 = nullptr;
	三维::C渲染控制 *m渲染控制 = nullptr;
	C二维::S资源 *m资源 = nullptr;
	数学::S颜色 m颜色;
	float m线条宽度 = 1;
};