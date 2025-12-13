
#include "header.h"
#include <codecvt>
#include <cstdio>
#include <fstream>
#include <locale>
#include <string>
#include <vector>
#include <iostream>

// 读取 UTF-8 文件内容到宽字符串
std::wstring
Read(const std::string& path)
{
    // 1. 以二进制方式读取文件
    std::ifstream file(path, std::ios::binary);
    if(!file) throw std::runtime_error("cannot open file");

    std::string utf8(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    // 2. UTF-8 -> UTF-16 / UTF-32
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(utf8);
}

void SendUnicodeChar(wchar_t c)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;

    input.ki.wScan   = c;
    input.ki.dwFlags = KEYEVENTF_UNICODE;

    SendInput(1, &input, sizeof(INPUT));
}

void
SendVKCode(wchar_t c)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;

    input.ki.wVk = c;

    SendInput(1, &input, sizeof(INPUT));
}

void 
print_wchar(wchar_t c)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::cout << conv.to_bytes(std::wstring(1, c));  // 转 UTF-8 输出
}
