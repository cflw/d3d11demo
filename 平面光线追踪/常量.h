#pragma once
constexpr float c帧秒 = 1.f / 60.f;	//一帧等于多少秒
constexpr int c窗口宽度 = 1280;
constexpr int c窗口高度 = 960;
constexpr int c基础宽度 = 640;
constexpr int c基础高度 = 480;
constexpr float c缩放 = (float)c窗口高度 / (float)c基础高度;
constexpr int c基础范围x = c基础宽度 * 0.5f;
constexpr int c基础范围y = c基础高度 * 0.5f;