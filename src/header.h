
#pragma once

#include <string>
#include <windows.h>

void SleepMS(int ms); // 以毫秒为单位的睡眠函数

std::wstring Read(const std::string& path); // 读取文件内容到宽字符串

void SendUnicodeChar(wchar_t c); // 发送 Unicode 字符
void SendVKCode(int c);          // 发送虚拟按键代码
void PrintWChar(wchar_t c);      // 打印宽字符到控制台

bool GetVKKey(int c);  // 检测按键是否按下
void WaitVKKey(int c); // 忙等待按键按下

// 抄写相关函数
void Copy(std::wstring context);  // 根据内容抄写
void MCopy(std::wstring context); // 根据内容适应抄写，自动处理换行和括号
