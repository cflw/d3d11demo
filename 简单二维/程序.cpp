#include <Windows.h>
#include <cflw时间.h>
#include "图形.h"
#include "常量.h"
namespace 时间 = cflw::时间;
class C程序 {
public:
	C图形 m图形;
	时间::C计时器 m计时器;
	void f初始化(HINSTANCE hInst, HINSTANCE = nullptr, LPSTR = nullptr, int = 0) {
		m实例 = hInst;
		f创建窗口();
		//图形
		m图形.f初始化(m窗口);
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
		const DWORD	c窗口风格 = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		const DWORD	c窗口风格ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		AdjustWindowRectEx(&v窗口矩形, c窗口风格, FALSE, c窗口风格ex);
		m窗口大小[0] = v窗口矩形.right - v窗口矩形.left;
		m窗口大小[1] = v窗口矩形.bottom - v窗口矩形.top;
		//创建窗口
		m窗口 = CreateWindowW(L"窗口类",	//窗口类名
			L"窗口标题",					//窗口标题
			c窗口风格,			//窗口风格
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