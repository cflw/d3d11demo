#include "图形.h"
#include "常量.h"
void C图形::f初始化(HWND a窗口) {
	m三维.f初始化(a窗口);
}
void C图形::f销毁() {
	m三维.f销毁();
}
void C图形::f计算() {

}
void C图形::f更新() {

}
void C图形::f显示() {
	auto &v渲染控制 = m三维.fg渲染控制();
	v渲染控制.f清屏();

	v渲染控制.f显示();
}