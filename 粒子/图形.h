#pragma once
#include <cflw��ѧ.h>
#include <cflwͼ��_d3d11.h>
#include "����.h"
namespace ��ѧ = cflw::��ѧ;
namespace ��ά = cflw::ͼ��::d3d11;
class Cͼ�� {
public:
	void f��ʼ��(HWND);
	void f����();
	void f����();
	void f����();
	void f��ʾ();
	��ά::C��ά m��ά;
	��ά::tp������ɫ�� m��ɫ��v;
	��ά::tp������ɫ�� m��ɫ��g;
	��ά::tp������ɫ�� m��ɫ��p;
	struct S���� {
		��ѧ::S����2 m���ڴ�С;
		float m���Ӵ�С;
	} m����;
	��ά::tp���� m���㻺��;
	S���� ma��������[c��������] = {};
	C���� ma���Ӷ���[c��������] = {};
};