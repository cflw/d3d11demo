﻿#include <cflw图形_d3d着色器.h>
#include <cflw文件_obj模型.h>
#include "图形.h"
#include "常量.h"
namespace 着色器 = cflw::图形::d3d着色器;
namespace 模型 = cflw::文件::obj;
void C图形::f初始化(HWND a窗口) {
	m三维.f初始化(a窗口);
	auto &v渲染控制 = m三维.fg渲染控制();
	auto &v渲染状态 = m三维.fg渲染状态();
	auto &v缓冲工厂 = m三维.fg缓冲工厂();
	auto &v纹理工厂 = m三维.fg纹理工厂();
	三维::C顶点格式 v顶点格式;
	三维::tp输入布局 v输入布局;
	v顶点格式.f添加(三维::C顶点格式::e位置, 3);
	v顶点格式.f添加(三维::C顶点格式::e纹理, 2);
	着色器::C着色器工厂 v着色器工厂;
	v着色器工厂.f初始化();
	着色器::tp着色器 vs, ps;
	v着色器工厂.f编译顶点着色器(vs, L"着色器.hlsl", "vs");
	v着色器工厂.f编译像素着色器(ps, L"着色器.hlsl", "ps");
	m三维.f创建顶点着色器(m着色器v, 着色器::fc跨度(vs));
	m三维.f创建输入布局(v输入布局, 着色器::fc跨度(vs), v顶点格式);
	m三维.f创建像素着色器(m着色器p, 着色器::fc跨度(ps));
	v渲染控制.fs顶点着色器(m着色器v.Get());
	v渲染控制.fs像素着色器(m着色器p.Get());
	v渲染控制.fs输入布局(v输入布局.Get());
	//顶点
	struct S顶点 {
		数学::S向量3 m坐标;
		数学::S向量2 m纹理;
	};
	模型::C对象模型 v模型;
	v模型.f打开(L"立方体.obj");
	std::vector<S顶点> va顶点;
	for (const auto &v索引 : v模型.ma索引) {
		S顶点 v顶点;
		const auto &v顶点坐标 = v模型.fg顶点(v索引);
		v顶点.m坐标 = {v顶点坐标.x, v顶点坐标.y, v顶点坐标.z};
		const auto &v纹理坐标 = v模型.fg纹理(v索引);
		v顶点.m纹理 = {v纹理坐标.u, v纹理坐标.v};
		va顶点.push_back(v顶点);
	}
	三维::tp缓冲 v顶点缓冲;
	v缓冲工厂.f创建缓冲(v顶点缓冲, va顶点.data(), sizeof(S顶点) * va顶点.size(), 三维::E缓冲::e顶点);
	v渲染控制.fs顶点缓冲(v顶点缓冲.Get(), sizeof(S顶点));
	//常量
	m总矩阵[0] = m世界.ft矩阵4();
	数学::S相机 v相机;
	v相机.m坐标 = {0, 0, 4};
	v相机.m目标 = {0, 0, 0};
	v相机.m上方 = {0, 1, 0};
	m总矩阵[1] = v相机.ft矩阵4r();
	数学::S透视投影 v投影 = {c基础宽度, c基础高度};
	m总矩阵[2] = v投影.ft矩阵4r();
	v缓冲工厂.f创建缓冲(m常量, m总矩阵, sizeof(m总矩阵), 三维::E缓冲::e常量);
	v渲染控制.fs常量缓冲(0, m常量.Get());
	//纹理
	三维::tp纹理资源视图 v纹理;
	v纹理工厂.f从文件创建纹理资源视图(v纹理, L"纹理.jpg");
	v渲染控制.fs纹理(0, v纹理.Get());
	v渲染控制.fs采样器(0, v渲染状态.m采样器.m纹理.Get());
	//其它状态
	v渲染控制.fs图元拓扑(三维::E图元拓扑::e列表三角形);
	v渲染控制.fs光栅化(v渲染状态.m光栅化.m反面渲染.Get());
	v渲染控制.fs混合(v渲染状态.m混合.m开启透明.Get());
	v渲染控制.fs深度模板(v渲染状态.m深度模板.m正常深度r.Get());
}
void C图形::f销毁() {
	m着色器v.Reset();
	m着色器p.Reset();
	m三维.f销毁();
}
void C图形::f计算() {
	m时间 += c帧秒;
}
void C图形::f更新() {
	auto &v渲染控制 = m三维.fg渲染控制();
	m世界.m旋转.x = m时间 * 0.9f;
	m世界.m旋转.y = m时间 * 0.5f;
	m世界.m旋转.z = m时间 * 0.2f;
	m总矩阵[0] = m世界.ft矩阵4();
	v渲染控制.f更新资源(m常量.Get(), m总矩阵);
}
void C图形::f显示() {
	auto &v渲染控制 = m三维.fg渲染控制();
	v渲染控制.f清屏();
	v渲染控制.f绘制(36);
	v渲染控制.f显示();
}