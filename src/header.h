
#pragma once

#include <windows.h>
#include <string>

std::wstring Read(const std::string& path);
void SendUnicodeChar(wchar_t c);
void SendVKCode(int c);

bool GetVKKey(int c);
void WaitVKKey(int c); // 等待按键按下

void Copy(std::wstring context);  // 根据内容抄写
void MCopy(std::wstring context); // 根据内容适应抄写，自动处理换行和括号