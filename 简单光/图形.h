#pragma once
#include <cflw��ѧ.h>
#include <cflw��ѧ_����.h>
#include <cflw��ѧ_ͼ��.h>
#include <cflw��ѧ_����.h>
#include <cflwͼ��_d3d11.h>
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
	��ά::tp������ɫ�� m��ɫ��p;
	��ά::tp���� m�̶�0, m�̶�1;
	��ѧ::S�������3 m����;
	��ѧ::S����2 m���ڴ�С;
	float m��;
	struct S�ܾ��� {
		��ѧ::S����4 m����, m��ͼ, mͶӰ;
	} m�ܾ���;
	struct S�� {
		��ѧ::S����3 mλ��;
		int32_t x0;	//���
		��ѧ::S��ɫ m��ɫ;
		float m��ʼ;
		float m��Χ;
	} m��;
};