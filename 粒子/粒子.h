#pragma once
#include "常量.h"
#include <cflw数学.h>
#include <cflw数学_向量.h>
#include <cflw数学_图形.h>
namespace 数学 = cflw::数学;
struct S粒子 {
	数学::S向量2 m坐标;
	数学::S颜色 m颜色;
};
class C粒子 {
public:
	void f初始化();
	void f计算();
	void f复制();
	数学::S向量2 m坐标;
	数学::S向量2 m速度;
	数学::S颜色 m颜色;
	float m寿命 = 0;
	float m时间 = 0;
	S粒子 *m目标;
};
