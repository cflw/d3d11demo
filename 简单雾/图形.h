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
	��ά::tp���� m�̶�;
	��ѧ::S�������3 m����;
	struct S�ܾ��� {
		��ѧ::S����4 m����, m��ͼ, mͶӰ;
	} m�ܾ���;
	��ѧ::S����2 m���ڴ�С;
};