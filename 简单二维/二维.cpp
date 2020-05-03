﻿#include <vector>
#include <cflw图形_d3d着色器.h>
#include "二维.h"
#include "常量.h"
namespace 着色器 = cflw::图形::d3d着色器;
//==============================================================================
// 二维
//==============================================================================
void C二维::f初始化(三维::C三维 &a三维) {
	m三维 = &a三维;
	auto &v渲染控制 = a三维.fg渲染控制();
	auto &v渲染状态 = a三维.fg渲染状态();
	auto &v缓冲工厂 = a三维.fg缓冲工厂();
	三维::C顶点格式 v顶点格式;
	三维::tp输入布局 v输入布局;
	v顶点格式.f添加(三维::C顶点格式::e位置, 2);
	着色器::C着色器工厂 v着色器工厂;
	v着色器工厂.f初始化();
	着色器::tp着色器 vs, ps;
	v着色器工厂.f编译顶点着色器(vs, L"着色器.hlsl", "vs");
	v着色器工厂.f编译像素着色器(ps, L"着色器.hlsl", "ps");
	a三维.f创建顶点着色器(m资源.m着色器v, 着色器::fc跨度(vs));
	a三维.f创建输入布局(v输入布局, 着色器::fc跨度(vs), v顶点格式);
	a三维.f创建像素着色器(m资源.m着色器p, 着色器::fc跨度(ps));
	v渲染控制.fs顶点着色器(m资源.m着色器v.Get());
	v渲染控制.fs像素着色器(m资源.m着色器p.Get());
	v缓冲工厂.f创建缓冲(m资源.m顶点缓冲, nullptr, sizeof(数学::S向量2) * c最大顶点数, 三维::E缓冲::e顶点);
	v渲染控制.fs顶点缓冲(m资源.m顶点缓冲.Get(), sizeof(数学::S向量2));
	v缓冲工厂.f创建缓冲(m资源.m矩形索引缓冲, ca矩形索引, sizeof(ca矩形索引), 三维::E缓冲::e索引);
	uint16_t va圆形索引[c圆形索引数] = {};
	for (int i = 0; i != c圆形边数 - 2; ++i) {
		const int v序号 = i * 3;
		va圆形索引[v序号] = 0;
		va圆形索引[v序号 + 1] = i + 1;
		va圆形索引[v序号 + 2] = i + 2;
	}
	v缓冲工厂.f创建缓冲(m资源.m圆形索引缓冲, va圆形索引, sizeof(va圆形索引), 三维::E缓冲::e索引);
	struct S顶点常量 {
		数学::S向量2 m窗口大小;
	} v顶点常量;
	v顶点常量.m窗口大小 = {c基础范围x, c基础范围y};
	v缓冲工厂.f创建缓冲(m资源.m顶点常量缓冲, &v顶点常量, sizeof(v顶点常量), 三维::E缓冲::e常量);
	v渲染控制.fs常量缓冲v(0, m资源.m顶点常量缓冲.Get());
	struct S像素常量 {
		数学::S颜色 m颜色;
	}v像素常量;
	v像素常量.m颜色 = 数学::S颜色::c白;
	v缓冲工厂.f创建缓冲(m资源.m像素常量缓冲, &v像素常量, sizeof(v像素常量), 三维::E缓冲::e常量);
	v渲染控制.fs常量缓冲p(1, m资源.m像素常量缓冲.Get());
	v渲染控制.fs输入布局(v输入布局.Get());
	v渲染控制.fs光栅化(v渲染状态.m光栅化.m显示隐藏面.Get());
	v渲染控制.fs混合(v渲染状态.m混合.m开启透明.Get());
	v渲染控制.fs深度模板(v渲染状态.m深度模板.m正常深度r.Get());
}
void C二维::f准备() {
}
std::shared_ptr<C画图形> C二维::fc画图形() {
	auto &v渲染控制 = m三维->fg渲染控制();
	auto v画图形 = std::make_unique<C画图形>(*this);
	return v画图形;
}
//==============================================================================
// 画图形
//==============================================================================
C画图形::C画图形(C二维 &a二维):
	m三维(a二维.m三维),
	m渲染控制(&a二维.m三维->fg渲染控制()),
	m资源(&a二维.m资源) {
}
//设置
void C画图形::fs线条宽度(float a) {
	m线条宽度 = a;
}
void C画图形::fs颜色(const 数学::S颜色 &a颜色) {
	m颜色 = a颜色;
	m渲染控制->f更新资源(m资源->m像素常量缓冲.Get(), &m颜色);
}
void C画图形::fs透明度(float a) {
	m颜色.a = a;
}
//描线
void C画图形::f绘制点(const 数学::S向量2 &a点) {
	//顶点
}
void C画图形::f绘制线条(const 数学::S线段2 &a线段) {
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e连续线段);

}
void C画图形::f绘制矩形(const 数学::S矩形 &) {

}
void C画图形::f绘制旋转矩形(const 数学::S旋转矩形 &a矩形) {

}
void C画图形::f绘制圆形(const 数学::S圆形 &) {

}
void C画图形::f绘制椭圆(const 数学::S椭圆 &) {

}
void C画图形::f绘制圆角矩形(const 数学::S圆角矩形 &) {

}
//填充
void C画图形::f填充矩形(const 数学::S矩形 &a矩形) {
	const 数学::S向量2 va顶点[] = {
		a矩形.fg点(-1, 1),
		a矩形.fg点(1, 1),
		a矩形.fg点(-1, -1),
		a矩形.fg点(1, -1),
	};
	m渲染控制->f更新资源(m资源->m顶点缓冲.Get(), va顶点);
	m渲染控制->fs索引缓冲(m资源->m矩形索引缓冲.Get());
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制->f绘制索引(C二维::c矩形索引数);
}
void C画图形::f填充旋转矩形(const 数学::S旋转矩形 &a矩形) {
	const 数学::S向量2 va顶点[] = {
		a矩形.fg点(-1, 1),
		a矩形.fg点(1, 1),
		a矩形.fg点(-1, -1),
		a矩形.fg点(1, -1),
	};
	m渲染控制->f更新资源(m资源->m顶点缓冲.Get(), va顶点);
	m渲染控制->fs索引缓冲(m资源->m矩形索引缓冲.Get());
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制->f绘制索引(C二维::c矩形索引数);
}
void C画图形::f填充圆形(const 数学::S圆形 &a圆形) {
	数学::S向量2 va顶点[C二维::c圆形顶点数];
	for (int i = 0; i != C二维::c圆形顶点数; ++i) {
		const float v方向 = (float)i / (float)C二维::c圆形顶点数 * 数学::c二π<float>;
		va顶点[i] = a圆形.fg点r(v方向);
	}
	m渲染控制->f更新资源(m资源->m顶点缓冲.Get(), va顶点);
	m渲染控制->fs索引缓冲(m资源->m圆形索引缓冲.Get());
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制->f绘制索引(C二维::c圆形索引数);
}
void C画图形::f填充椭圆(const 数学::S椭圆 &) {

}
void C画图形::f填充圆角矩形(const 数学::S圆角矩形 &) {

}