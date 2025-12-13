
#pragma once

#include <windows.h>
#include <string>

std::wstring Read(const std::string& path);
void SendUnicodeChar(wchar_t c);
void SendVKCode(wchar_t c);

void print_wchar(wchar_t c);