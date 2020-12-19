#include <random>
#include <ctime>
#include "粒子.h"
#include "常量.h"
//==============================================================================
// 光
//==============================================================================
void C光::f初始化(const 数学::S向量2 &a坐标, float a方向) {
	m坐标 = a坐标;
	m方向 = a方向;
}
void C光::f计算() {
	m时间 += c帧秒;
}
float C光::fg方向() const {
	//return m方向;
	return m方向 + std::sin(m时间 * 0.5f) * c旋转角度;
}
S光顶点 C光::fg顶点(float x, float y) const {
	const float v边缘方向 = std::atan2(m半宽1 - m半宽0, c长度);
	const float v相对方向 = std::lerp(0, v边缘方向, y);
	const 数学::S向量2 v相对坐标 = {c长度 * x, std::lerp(m半宽0, m半宽1, x) * y};
	const float v光方向 = fg方向();
	return {m坐标 + v相对坐标.f旋转r(v光方向), 数学::S向量2::fc方向r(1, v光方向 + v相对方向), m颜色};
}
//==============================================================================
// 圆
//==============================================================================
void C圆::f初始化(const 数学::S向量2 &a坐标, const 数学::S向量2 &a速度, float a半径) {
	m坐标 = a坐标;
	m速度 = a速度;
	m半径 = a半径;
}
void C圆::f计算() {
	m坐标 += m速度 * c帧秒;
	const auto f反弹 = [&](float &a坐标, float &a速度, float a翻折, std::function<bool(float, float)> af比较) {
		if (af比较(a坐标, a翻折)) {
			a坐标 = 数学::f翻折(a坐标, a翻折);
			a速度 = -a速度;
		}
	};
	f反弹(m坐标.x, m速度.x, c基础范围x, std::greater<float>());
	f反弹(m坐标.x, m速度.x, -c基础范围x, std::less<float>());
	f反弹(m坐标.y, m速度.y, c基础范围y, std::greater<float>());
	f反弹(m坐标.y, m速度.y, -c基础范围y, std::less<float>());
}
数学::S向量2 C圆::fg半径向量() const {
	return 数学::S向量2::fc相同(m半径);
}
S圆顶点 C圆::fg顶点() const {
	return {m坐标, fg半径向量(), m颜色};
}
S圆常量 C圆::fg常量() const {
	return {m坐标, fg半径向量()};
}
//==============================================================================
// 粒子管理
//==============================================================================
void C粒子管理::f初始化() {
	//光1
	ma光[0].f初始化(数学::S向量2(-c基础范围x, c基础范围y), 数学::c二π<float> * 7.f / 8.f);
	ma光[1].f初始化(数学::S向量2(c基础范围x, c基础范围y), 数学::c二π<float> * 5.f / 8.f);
	//圆
	std::default_random_engine v随机数引擎;
	v随机数引擎.seed(std::time(0));
	const std::uniform_real_distribution<float> c坐标分布x{-c基础范围x, c基础范围x};
	const std::uniform_real_distribution<float> c坐标分布y{-c基础范围y, c基础范围y};
	const std::uniform_real_distribution<float> c圆周分布{0, 数学::c二π<float>};
	const std::uniform_real_distribution<float> c半径大小分布{10, 50};
	const std::uniform_real_distribution<float> c速度大小分布{50, 100};
	for (C圆 &v圆 : ma圆) {
		v圆.f初始化(
			数学::S向量2(c坐标分布x(v随机数引擎), c坐标分布y(v随机数引擎)), 
			数学::S向量2::fc方向r(c速度大小分布(v随机数引擎), c圆周分布(v随机数引擎)),
			c半径大小分布(v随机数引擎)
		);
	}
}
void C粒子管理::f计算() {
	for (C光 &v光 : ma光) {
		v光.f计算();
	}
	for (C圆 &v圆 : ma圆) {
		v圆.f计算();
	}
}
