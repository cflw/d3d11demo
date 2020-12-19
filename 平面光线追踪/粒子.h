#pragma once
#include <cflw数学_向量.h>
#include <cflw数学_图形.h>
namespace 数学 = cflw::数学;
constexpr int c光数量 = 2;
constexpr int c光每顶点数 = 4;
constexpr int c光顶点数 = c光数量 * c光每顶点数;
constexpr int c圆数量 = 10;
constexpr int c圆每顶点数 = 1;
constexpr int c圆顶点数 = c圆数量 * c圆每顶点数;
constexpr int c总顶点数 = std::max(c光顶点数, c圆顶点数);
struct S光顶点 {
	数学::S向量2 m坐标;
	数学::S向量2 m方向;
	数学::S颜色 m颜色;
};
struct S圆顶点 {
	数学::S向量2 m坐标;
	数学::S向量2 m半径;
	数学::S颜色 m颜色;
};
struct S圆常量 {
	数学::S向量2 m坐标;
	数学::S向量2 m半径;
};
class C光 {
public:
	static constexpr float c旋转角度 = 数学::c二π<float> / 8.f;
	static constexpr float c长度 = 1000;
	void f初始化(const 数学::S向量2 &坐标, float 方向);
	void f计算();
	float fg方向() const;
	S光顶点 fg顶点(float, float) const;
	数学::S向量2 m坐标;
	数学::S颜色 m颜色 = 数学::S颜色(1, 1, 0.5f, 0.5f);
	float m半宽0 = 50;
	float m半宽1 = 200;
	float m方向 = 0;
	float m时间 = 0;
};
class C圆 {
public:
	void f初始化(const 数学::S向量2 &坐标, const 数学::S向量2 &速度, float 半径);
	void f计算();
	数学::S向量2 fg半径向量() const;
	S圆顶点 fg顶点() const;
	S圆常量 fg常量() const;
	数学::S向量2 m坐标;
	数学::S向量2 m速度;
	数学::S颜色 m颜色 = 数学::S颜色(1, 1, 1, 0.8f);
	float m半径 = 50;
};
class C粒子管理 {
public:
	void f初始化();
	void f计算();
	C光 ma光[c光数量];
	C圆 ma圆[c圆数量];
};
