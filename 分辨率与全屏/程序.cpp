#include <Windows.h>
#include <cflw时间.h>
#include <cflw输入_win.h>
#include <cflw视窗.h>
#include "图形.h"
#include "常量.h"
namespace 时间 = cflw::时间;
namespace 视窗 = cflw::视窗;
namespace 输入 = cflw::输入::win;
constexpr std::pair<int, int> ca分辨率[] = {
	{800, 600},
	{1024, 768},
	{1200, 900},
	{1280, 720},
	{1920, 1080},
	{1920, 1200},
};
constexpr int c分辨率数 = std::distance(std::begin(ca分辨率), std::end(ca分辨率));
class C程序 {
public:
	C图形 m图形;
	时间::C计时器 m计时器;
	输入::C输入 m输入;
	输入::tp键盘 m键盘;
	int m分辨率索引 = 0;
	bool m全屏 = false;
	C程序() {
		g这 = this;
	}
	void f初始化(HINSTANCE hInst, HINSTANCE = nullptr, LPSTR = nullptr, int = 0) {
		m实例 = hInst;
		f创建窗口();
		//图形
		m图形.f初始化(m窗口);
		//输入
		m输入.f初始化(m窗口);
		m输入.f创建键盘(m键盘);
		//计时器
		m计时器.f重置(c帧秒);
	}
	void f运行() {
		f消息循环();
	}
	void f关闭() {
		m图形.f销毁();
	}
	void f计算() {
		m输入.f更新();
		int v分辨率索引 = m分辨率索引;
		if (m键盘->f按键((int)输入::E键盘按键::e左).f刚按下()) {
			--v分辨率索引;
		} else if (m键盘->f按键((int)输入::E键盘按键::e右).f刚按下()) {
			++v分辨率索引;
		} else if (m键盘->f按键((int)输入::E键盘按键::e回车).f刚按下() && m键盘->f按键((int)输入::E键盘按键::e交替).f按下()) {
			m全屏 = !m全屏;
			m图形.fs全屏(m全屏);
		}
		if (v分辨率索引 != m分辨率索引) {
			m分辨率索引 = 数学::f求余(v分辨率索引, c分辨率数);
			const auto &[v宽, v高] = ca分辨率[m分辨率索引];
			m图形.fs窗口大小(v宽, v高);
			m图形.f重置();
			//改标题
			std::wstringstream v窗口标题;
			v窗口标题 << v宽 << L"*" << v高 << L",全屏" << m图形.m三维.fi全屏();
			视窗::fs窗口标题(m窗口, v窗口标题.str().c_str());
		}
		m图形.f计算();
	}
	void f更新() {
		m图形.f更新();
	}
	void f显示() {
		m图形.f显示();
	}
	//消息过程
	static LRESULT WINAPI f窗口过程(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		g这->m输入.f窗口消息(msg, wParam, lParam);
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		//使用默认处理
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	//创建窗口
	void f创建窗口() {
		//注册窗口
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);			//使用sizeof(WNDCLASSEX)
		wc.style = CS_CLASSDC;					//窗口类型
		wc.lpfnWndProc = f窗口过程;					//窗口过程
		wc.cbClsExtra = 0L;							//扩展:
		wc.cbWndExtra = 0L;							//扩展:
		wc.hInstance = m实例;						//实例句柄
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);	//载入默认图标
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//载入默认光标
		wc.hbrBackground = nullptr;							//不需要背景
		wc.lpszMenuName = nullptr;							//不需要菜单
		wc.lpszClassName = L"窗口类";					//设置类名
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		//计算窗口大小
		RECT v窗口矩形 = {0, 0, c窗口宽度, c窗口高度};
		const DWORD	c窗口样式 = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		const DWORD	c窗口样式ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		AdjustWindowRectEx(&v窗口矩形, c窗口样式, FALSE, c窗口样式ex);
		m窗口大小[0] = v窗口矩形.right - v窗口矩形.left;
		m窗口大小[1] = v窗口矩形.bottom - v窗口矩形.top;
		//创建窗口
		m窗口 = CreateWindowExW(
			c窗口样式ex,
			L"窗口类",	//窗口类名
			L"窗口标题",					//窗口标题
			c窗口样式,			//窗口样式
			CW_USEDEFAULT, CW_USEDEFAULT,	//坐标
			m窗口大小[0], m窗口大小[1],		//窗口尺寸
			GetDesktopWindow(),				//窗口句柄参数
			nullptr,							//菜单句柄
			wc.hInstance,					//实例句柄
			nullptr);							//参数
		//显示窗口
		ShowWindow(m窗口, SW_SHOWDEFAULT);
		UpdateWindow(m窗口);
		//取窗口客户区大小
		GetClientRect(m窗口, &v窗口矩形);
		m窗口大小[0] = v窗口矩形.right - v窗口矩形.left;
		m窗口大小[1] = v窗口矩形.bottom - v窗口矩形.top;
	}
	//消息循环
	void f消息循环() {
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {	//消息循环
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//有消息时的处理,不要修改
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//没有消息时的处理
				if (m计时器.f滴答()) {
					f计算();
					f更新();
					f显示();
				} else {
					Sleep(0);
				}
			}
		}	//消息循环结束
	}
	//全局变量
	HINSTANCE m实例;
	HWND m窗口;
	int m窗口大小[2];
	static C程序 *g这;
};
C程序 *C程序::g这 = nullptr;
//主函数
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
	C程序 v程序;
	v程序.f初始化(hInst);
	v程序.f运行();
	v程序.f关闭();
}