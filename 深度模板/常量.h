#pragma once
constexpr float c帧秒 = 1.f / 60.f;	//一帧等于多少秒
constexpr int c窗口宽度 = 640;
constexpr int c窗口高度 = 480;
constexpr int c基础宽度 = 640;
constexpr int c基础高度 = 480;
constexpr float c缩放 = (float)c窗口高度 / (float)c基础高度;

constexpr int c三角形数 = 7;
constexpr int c三角形顶点数 = c三角形数 * 3;
constexpr int c圆边数 = 32;
constexpr float c圆半径 = 200;
constexpr int c圆顶点数 = c圆边数 + 1;
constexpr int c圆索引数 = c圆边数 * 3;