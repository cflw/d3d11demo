#include <execution>
#include <functional>
#include <cflw图形_d3d着色器.h>
#include "图形.h"
namespace 着色器 = cflw::图形::d3d着色器;
void C图形::f初始化(HWND a窗口) {
	m三维.f初始化(a窗口);
	auto &v渲染控制 = m三维.fg渲染控制();
	auto &v渲染状态 = m三维.fg渲染状态();
	auto &v缓冲工厂 = m三维.fg缓冲工厂();
	//着色器
	三维::C顶点格式 v顶点格式;
	三维::tp输入布局 v输入布局;
	v顶点格式.f添加(三维::C顶点格式::e位置, 2);
	v顶点格式.f添加(三维::C顶点格式::e颜色, 4);
	着色器::C着色器工厂 v着色器工厂;
	v着色器工厂.f初始化();
	着色器::tp着色器 vs, ps, gs;
	v着色器工厂.f编译顶点着色器(vs, L"着色器.hlsl", "vs");
	v着色器工厂.f编译几何着色器(gs, L"着色器.hlsl", "gs");
	v着色器工厂.f编译像素着色器(ps, L"着色器.hlsl", "ps");
	m三维.f创建顶点着色器(m着色器v, 着色器::fc跨度(vs));
	m三维.f创建输入布局(v输入布局, 着色器::fc跨度(vs), v顶点格式);
	m三维.f创建几何着色器(m着色器g, 着色器::fc跨度(gs));
	m三维.f创建像素着色器(m着色器p, 着色器::fc跨度(ps));
	v渲染控制.fs顶点着色器(m着色器v.Get());
	v渲染控制.fs几何着色器(m着色器g.Get());
	v渲染控制.fs像素着色器(m着色器p.Get());
	v渲染控制.fs输入布局(v输入布局.Get());
	//顶点
	v缓冲工厂.f创建缓冲(m顶点缓冲, ma粒子数据, sizeof(ma粒子数据), 三维::E缓冲::e顶点);
	//常量
	m常量.m窗口大小 = 数学::S向量2(640, 480);
	m常量.m粒子大小 = c粒子半径;
	三维::tp缓冲 v常量缓冲;
	v缓冲工厂.f创建缓冲(v常量缓冲, &m常量, sizeof(m常量), 三维::E缓冲::e常量);
	v渲染控制.fs常量缓冲(0, v常量缓冲.Get());
	//其它
	v渲染控制.fs顶点缓冲(m顶点缓冲.Get(), sizeof(S粒子));
	v渲染控制.fs图元拓扑(三维::E图元拓扑::e列表点);
	v渲染控制.fs光栅化(v渲染状态.m光栅化.m显示隐藏面.Get());
	v渲染控制.fs混合(v渲染状态.m混合.m颜色叠加.Get());
	v渲染控制.fs深度模板(v渲染状态.m深度模板.m正常深度r.Get());
	for (int i = 0; i != c粒子数量; ++i) {
		ma粒子对象[i].m目标 = &ma粒子数据[i];
	}
}
void C图形::f销毁() {
	m着色器v.Reset();
	m着色器p.Reset();
	m三维.f销毁();
}
void C图形::f计算() {
	std::for_each(std::execution::par, 
		std::begin(ma粒子对象), std::end(ma粒子对象), 
		std::bind(&C粒子::f计算, std::placeholders::_1));
}
void C图形::f更新() {
	auto &v渲染控制 = m三维.fg渲染控制();
	std::for_each(std::execution::par_unseq, 
		std::begin(ma粒子对象), std::end(ma粒子对象), 
		std::bind(&C粒子::f复制, std::placeholders::_1));
	v渲染控制.f更新资源(m顶点缓冲.Get(), ma粒子数据);
}
void C图形::f显示() {
	auto &v渲染控制 = m三维.fg渲染控制();
	v渲染控制.f清屏();
	v渲染控制.f绘制(c粒子数量);
	v渲染控制.f显示();
}