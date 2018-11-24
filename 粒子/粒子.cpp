#include <time.h>
#include <random>
#include <mutex>
#include "粒子.h"
std::default_random_engine g随机数引擎((int)time(0));
std::uniform_real_distribution<float> g速度分布(1, 100);
std::uniform_real_distribution<float> g方向分布(0, 数学::c二π);
std::uniform_real_distribution<float> g寿命分布(1, 10);
std::uniform_real_distribution<float> g颜色分布(0, 7);
std::uniform_real_distribution<float> g透明分布(0.1f, 1.f);
std::mutex g随机数互斥;
void C粒子::f初始化() {
	std::lock_guard<std::mutex> v锁(g随机数互斥);
	m坐标 = 数学::S向量2::c零;
	m速度 = 数学::S向量2::fc方向r(g速度分布(g随机数引擎), g方向分布(g随机数引擎));
	m颜色 = 数学::S颜色::fc彩虹(g颜色分布(g随机数引擎), g透明分布(g随机数引擎));
	m寿命 = g寿命分布(g随机数引擎);
	m时间 = 0;
}
void C粒子::f计算() {
	if (m时间 >= m寿命) {
		f初始化();
	}
	if (m坐标.y > c基础高度 + 10) {
		f初始化();
	}
	m坐标 += m速度 * c帧秒;
	m时间 += c帧秒;
}
void C粒子::f复制() {
	m目标->m坐标 = m坐标;
	m目标->m颜色 = m颜色;
	m目标->m颜色.a = m颜色.a * (m寿命 - m时间) / m寿命;
}
