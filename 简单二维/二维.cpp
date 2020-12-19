#include <vector>
#include <cflw图形_d3d着色器.h>
#include "二维.h"
#include "常量.h"
namespace 着色器 = cflw::图形::d3d着色器;
//常量
static constexpr int c圆形边数 = 32;
static constexpr int c圆形顶点数 = c圆形边数;
static constexpr int c四分圆边数 = c圆形边数 / 4;
static constexpr int c最大顶点数 = 1000;
static constexpr uint16_t ca矩形索引[] = {
	0, 1, 2,
	1, 3, 2,
};
static constexpr int c矩形索引数 = _countof(ca矩形索引);
static constexpr int c圆形索引数 = (c圆形边数 - 2) * 3;
static constexpr int c最大索引数 = c最大顶点数 * 4;
//==============================================================================
// 资源管理
//==============================================================================
class C二维::C资源管理 {
public:
	struct S缓冲状态 {
		std::unique_ptr<std::byte[]> m数据;
		size_t m序号 = 0, m数量 = 0;
		S缓冲状态(size_t a大小):
			m数据(std::make_unique<std::byte[]>(a大小)) {
			memset(m数据.get(), 0, a大小);
		}
		void f重置() {
			m序号 = 0;
			m数量 = 0;
		}
		template<typename t>
		std::pair<t *, size_t> f申请(size_t a数量) {
			m序号 = m数量;
			m数量 += a数量;
			return { reinterpret_cast<t *>(m数据.get()) + m序号, m序号 };
		}
	};
	void f重置缓冲() {
		m顶点缓冲状态.f重置();
		m索引缓冲状态.f重置();
	}
	void f更新缓冲(ID3D11DeviceContext *a上下文) {
		a上下文->UpdateSubresource(m顶点缓冲.Get(), 0, nullptr, m顶点缓冲状态.m数据.get(), 0, 0);
		a上下文->UpdateSubresource(m索引缓冲.Get(), 0, nullptr, m索引缓冲状态.m数据.get(), 0, 0);
	}
	std::pair<S顶点 *, size_t> f申请顶点(size_t a数量) {
		return m顶点缓冲状态.f申请<S顶点>(a数量);
	}
	std::pair<uint16_t *, size_t> f申请索引(size_t a数量) {
		return m索引缓冲状态.f申请<uint16_t>(a数量);
	}
public:
	三维::tp输入布局 m输入布局;
	三维::tp缓冲 m顶点缓冲, m索引缓冲;
	三维::tp顶点着色器 m着色器v;
	三维::tp像素着色器 m着色器p;
	三维::tp缓冲 m顶点常量缓冲;
	//维护用的变量
	S缓冲状态 m顶点缓冲状态{sizeof(S顶点) * c最大顶点数}, m索引缓冲状态{sizeof(uint16_t) * c最大索引数};
};
//==============================================================================
// 二维
//==============================================================================
C二维::C二维() {
}
C二维::~C二维() {
}
void C二维::f初始化(三维::C三维 &a三维) {
	m三维 = &a三维;
	auto &v渲染控制 = a三维.fg渲染控制();
	auto &v缓冲工厂 = a三维.fg缓冲工厂();
	auto &v资源 = fg资源管理();
	三维::C顶点格式 v顶点格式;
	v顶点格式.f添加(三维::C顶点格式::e位置, 2);
	v顶点格式.f添加(三维::C顶点格式::e颜色, 4);
	着色器::C着色器工厂 v着色器工厂;
	v着色器工厂.f初始化();
	着色器::tp着色器 vs, ps;
	v着色器工厂.f编译顶点着色器(vs, L"着色器.hlsl", "vs");
	v着色器工厂.f编译像素着色器(ps, L"着色器.hlsl", "ps");
	a三维.f创建顶点着色器(v资源.m着色器v, 着色器::fc跨度(vs));
	a三维.f创建输入布局(v资源.m输入布局, 着色器::fc跨度(vs), v顶点格式);
	a三维.f创建像素着色器(v资源.m着色器p, 着色器::fc跨度(ps));
	v缓冲工厂.f创建缓冲(v资源.m顶点缓冲, nullptr, sizeof(S顶点) * c最大顶点数, 三维::E缓冲::e顶点);
	v缓冲工厂.f创建缓冲(v资源.m索引缓冲, nullptr, sizeof(uint16_t) * c最大索引数, 三维::E缓冲::e索引);
	struct S顶点常量 {
		数学::S向量2 m窗口大小;
	} v顶点常量;
	v顶点常量.m窗口大小 = {c基础范围x, c基础范围y};
	v缓冲工厂.f创建缓冲(v资源.m顶点常量缓冲, &v顶点常量, sizeof(v顶点常量), 三维::E缓冲::e常量);
}
void C二维::f开始() {
	auto &v资源 = fg资源管理();
	v资源.f重置缓冲();
}
void C二维::f结束() {
	auto &v渲染控制 = m三维->fg渲染控制();
	auto &v渲染状态 = m三维->fg渲染状态();
	auto &v资源 = fg资源管理();
	v资源.f更新缓冲(m三维->fg上下文().Get());
	v渲染控制.fs顶点着色器(v资源.m着色器v.Get());
	v渲染控制.fs像素着色器(v资源.m着色器p.Get());
	v渲染控制.fs常量缓冲v(0, v资源.m顶点常量缓冲.Get());
	v渲染控制.fs输入布局(v资源.m输入布局.Get());
	v渲染控制.fs光栅化(v渲染状态.m光栅化.m显示隐藏面.Get());
	v渲染控制.fs混合(v渲染状态.m混合.m开启透明.Get());
	v渲染控制.fs深度模板(v渲染状态.m深度模板.m正常深度r.Get());
	v渲染控制.fs顶点缓冲(v资源.m顶点缓冲.Get(), sizeof(S顶点));
	v渲染控制.fs索引缓冲(v资源.m索引缓冲.Get());
	v渲染控制.fs图元拓扑(三维::E图元拓扑::e列表三角形);
	v渲染控制.f绘制索引(m资源管理->m索引缓冲状态.m数量);
}
std::shared_ptr<C画图形> C二维::fc画图形() {
	auto &v渲染控制 = m三维->fg渲染控制();
	auto v画图形 = std::make_unique<C画图形>(*this);
	return v画图形;
}
C二维::C资源管理 &C二维::fg资源管理() {
	if (m资源管理 == nullptr) {
		m资源管理 = std::make_unique<C资源管理>();
	}
	return *m资源管理;
}
//==============================================================================
// 画图形
//==============================================================================
C画图形::C画图形(C二维 &a二维):
	m资源管理(&a二维.fg资源管理()) {
}
//设置
void C画图形::fs线条宽度(float a) {
	m线条宽度 = a;
}
void C画图形::fs颜色(const 数学::S颜色 &a颜色) {
	m颜色 = a颜色;
}
void C画图形::fs透明度(float a) {
	m颜色.a = a;
}
//描线
void C画图形::f绘制点(const 数学::S向量2 &a点) {
	//顶点
}
void C画图形::f绘制线条(const 数学::S线段2 &a线段) {

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
	const auto &[vp顶点, v顶点序号] = m资源管理->f申请顶点(4);
	const auto &[vp索引, v索引序号] = m资源管理->f申请索引(6);
	//顶点
	vp顶点[0].m坐标 = a矩形.fg点(-1, 1);
	vp顶点[1].m坐标 = a矩形.fg点(1, 1);
	vp顶点[2].m坐标 = a矩形.fg点(-1, -1);
	vp顶点[3].m坐标 = a矩形.fg点(1, -1);
	for (int i = 0; i != 4; ++i) {
		vp顶点[i].m颜色 = m颜色;
	}
	//索引
	for (int i = 0; i != 6; ++i) {
		vp索引[i] = v顶点序号 + ca矩形索引[i];
	}
}
void C画图形::f填充旋转矩形(const 数学::S旋转矩形 &a矩形) {
	const auto &[vp顶点, v顶点序号] = m资源管理->f申请顶点(4);
	const auto &[vp索引, v索引序号] = m资源管理->f申请索引(6);
	//顶点
	vp顶点[0].m坐标 = a矩形.fg点(-1, 1);
	vp顶点[1].m坐标 = a矩形.fg点(1, 1);
	vp顶点[2].m坐标 = a矩形.fg点(-1, -1);
	vp顶点[3].m坐标 = a矩形.fg点(1, -1);
	for (int i = 0; i != 4; ++i) {
		vp顶点[i].m颜色 = m颜色;
	}
	//索引
	for (int i = 0; i != 6; ++i) {
		vp索引[i] = v顶点序号 + ca矩形索引[i];
	}
}
void C画图形::f填充圆形(const 数学::S圆形 &a圆形) {
	const int v顶点数 = static_cast<int>(std::sqrt(a圆形.m半径) * 4);
	const int v索引数 = (v顶点数 - 2) * 3;
	const auto &[vp顶点, v顶点序号] = m资源管理->f申请顶点(v顶点数);
	const auto &[vp索引, v索引序号] = m资源管理->f申请索引(v索引数);
	//顶点
	for (int i = 0; i != v顶点数; ++i) {
		const float v方向 = (float)i / (float)v顶点数 * 数学::c二π<float>;
		vp顶点[i].m坐标 = a圆形.fg点r(v方向);
		vp顶点[i].m颜色 = m颜色;
	}
	//索引
	for (int i = 0; i != v顶点数 - 2; ++i) {
		const int v序号 = i * 3;
		vp索引[v序号] = v顶点序号 + 0;
		vp索引[v序号 + 1] = v顶点序号 + i + 1;
		vp索引[v序号 + 2] = v顶点序号 + i + 2;
	}
}
void C画图形::f填充椭圆(const 数学::S椭圆 &) {

}
void C画图形::f填充圆角矩形(const 数学::S圆角矩形 &) {

}
void C画图形::f填充三角形(const 数学::S三角形 &a三角形) {
	const auto &[vp顶点, v顶点序号] = m资源管理->f申请顶点(3);
	const auto &[vp索引, v索引序号] = m资源管理->f申请索引(3);
	for (int i = 0; i != 3; ++i) {
		vp顶点[i].m坐标 = a三角形.m点[i];
		vp顶点[i].m颜色 = m颜色;
		vp索引[i] = v顶点序号 + i;
	}
}