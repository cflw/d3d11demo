#include <time.h>
#include <random>
#include <mutex>
#include "����.h"
std::default_random_engine g���������((int)time(0));
std::uniform_real_distribution<float> g�ٶȷֲ�(1, 100);
std::uniform_real_distribution<float> g����ֲ�(0, ��ѧ::c����);
std::uniform_real_distribution<float> g�����ֲ�(1, 10);
std::uniform_real_distribution<float> g��ɫ�ֲ�(0, 7);
std::uniform_real_distribution<float> g͸���ֲ�(0.1f, 1.f);
std::mutex g���������;
void C����::f��ʼ��() {
	std::lock_guard<std::mutex> v��(g���������);
	m���� = ��ѧ::S����2::c��;
	m�ٶ� = ��ѧ::S����2::fc����r(g�ٶȷֲ�(g���������), g����ֲ�(g���������));
	m��ɫ = ��ѧ::S��ɫ::fc�ʺ�(g��ɫ�ֲ�(g���������), g͸���ֲ�(g���������));
	m���� = g�����ֲ�(g���������);
	mʱ�� = 0;
}
void C����::f����() {
	if (mʱ�� >= m����) {
		f��ʼ��();
	}
	if (m����.y > c�����߶� + 10) {
		f��ʼ��();
	}
	m���� += m�ٶ� * c֡��;
	mʱ�� += c֡��;
}
void C����::f����() {
	mĿ��->m���� = m����;
	mĿ��->m��ɫ = m��ɫ;
	mĿ��->m��ɫ.a = m��ɫ.a * (m���� - mʱ��) / m����;
}
