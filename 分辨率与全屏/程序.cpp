#include <Windows.h>
#include <cflwʱ��.h>
#include <cflw����_win.h>
#include <cflw�Ӵ�.h>
#include "ͼ��.h"
#include "����.h"
namespace ʱ�� = cflw::ʱ��;
namespace �Ӵ� = cflw::�Ӵ�;
namespace ���� = cflw::����::win;
constexpr std::pair<int, int> ca�ֱ���[] = {
	{800, 600},
	{1024, 768},
	{1200, 900},
	{1280, 720},
	{1920, 1080},
	{1920, 1200},
};
constexpr int c�ֱ����� = std::distance(std::begin(ca�ֱ���), std::end(ca�ֱ���));
class C���� {
public:
	Cͼ�� mͼ��;
	ʱ��::C��ʱ�� m��ʱ��;
	����::C���� m����;
	����::tp���� m����;
	int m�ֱ������� = 0;
	bool mȫ�� = false;
	C����() {
		g�� = this;
	}
	void f��ʼ��(HINSTANCE hInst, HINSTANCE = nullptr, LPSTR = nullptr, int = 0) {
		mʵ�� = hInst;
		f��������();
		//ͼ��
		mͼ��.f��ʼ��(m����);
		//����
		m����.f��ʼ��(m����);
		m����.f��������(m����);
		//��ʱ��
		m��ʱ��.f����(c֡��);
	}
	void f����() {
		f��Ϣѭ��();
	}
	void f�ر�() {
		mͼ��.f����();
	}
	void f����() {
		m����.f����();
		int v�ֱ������� = m�ֱ�������;
		if (m����->f����((int)����::E���̰���::e��).f�հ���()) {
			--v�ֱ�������;
		} else if (m����->f����((int)����::E���̰���::e��).f�հ���()) {
			++v�ֱ�������;
		} else if (m����->f����((int)����::E���̰���::e�س�).f�հ���() && m����->f����((int)����::E���̰���::e����).f����()) {
			mȫ�� = !mȫ��;
			mͼ��.fsȫ��(mȫ��);
		}
		if (v�ֱ������� != m�ֱ�������) {
			m�ֱ������� = ��ѧ::f����(v�ֱ�������, c�ֱ�����);
			const auto &[v��, v��] = ca�ֱ���[m�ֱ�������];
			mͼ��.fs���ڴ�С(v��, v��);
			mͼ��.f����();
			//�ı���
			std::wstringstream v���ڱ���;
			v���ڱ��� << v�� << L"*" << v�� << L",ȫ��" << mͼ��.m��ά.fiȫ��();
			�Ӵ�::fs���ڱ���(m����, v���ڱ���.str().c_str());
		}
		mͼ��.f����();
	}
	void f����() {
		mͼ��.f����();
	}
	void f��ʾ() {
		mͼ��.f��ʾ();
	}
	//��Ϣ����
	static LRESULT WINAPI f���ڹ���(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		g��->m����.f������Ϣ(msg, wParam, lParam);
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		//ʹ��Ĭ�ϴ���
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	//��������
	void f��������() {
		//ע�ᴰ��
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);			//ʹ��sizeof(WNDCLASSEX)
		wc.style = CS_CLASSDC;					//��������
		wc.lpfnWndProc = f���ڹ���;					//���ڹ���
		wc.cbClsExtra = 0L;							//��չ:
		wc.cbWndExtra = 0L;							//��չ:
		wc.hInstance = mʵ��;						//ʵ�����
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);	//����Ĭ��ͼ��
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//����Ĭ�Ϲ��
		wc.hbrBackground = nullptr;							//����Ҫ����
		wc.lpszMenuName = nullptr;							//����Ҫ�˵�
		wc.lpszClassName = L"������";					//��������
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		//���㴰�ڴ�С
		RECT v���ھ��� = {0, 0, c���ڿ��, c���ڸ߶�};
		const DWORD	c������ʽ = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		const DWORD	c������ʽex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		AdjustWindowRectEx(&v���ھ���, c������ʽ, FALSE, c������ʽex);
		m���ڴ�С[0] = v���ھ���.right - v���ھ���.left;
		m���ڴ�С[1] = v���ھ���.bottom - v���ھ���.top;
		//��������
		m���� = CreateWindowExW(
			c������ʽex,
			L"������",	//��������
			L"���ڱ���",					//���ڱ���
			c������ʽ,			//������ʽ
			CW_USEDEFAULT, CW_USEDEFAULT,	//����
			m���ڴ�С[0], m���ڴ�С[1],		//���ڳߴ�
			GetDesktopWindow(),				//���ھ������
			nullptr,							//�˵����
			wc.hInstance,					//ʵ�����
			nullptr);							//����
		//��ʾ����
		ShowWindow(m����, SW_SHOWDEFAULT);
		UpdateWindow(m����);
		//ȡ���ڿͻ�����С
		GetClientRect(m����, &v���ھ���);
		m���ڴ�С[0] = v���ھ���.right - v���ھ���.left;
		m���ڴ�С[1] = v���ھ���.bottom - v���ھ���.top;
	}
	//��Ϣѭ��
	void f��Ϣѭ��() {
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {	//��Ϣѭ��
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//����Ϣʱ�Ĵ���,��Ҫ�޸�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//û����Ϣʱ�Ĵ���
				if (m��ʱ��.f�δ�()) {
					f����();
					f����();
					f��ʾ();
				} else {
					Sleep(0);
				}
			}
		}	//��Ϣѭ������
	}
	//ȫ�ֱ���
	HINSTANCE mʵ��;
	HWND m����;
	int m���ڴ�С[2];
	static C���� *g��;
};
C���� *C����::g�� = nullptr;
//������
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
	C���� v����;
	v����.f��ʼ��(hInst);
	v����.f����();
	v����.f�ر�();
}