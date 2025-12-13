
#include "header.h"

#include <chrono>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <thread>


std::wstring utf8_to_wstring(const std::string& s)
{
    int len = MultiByteToWideChar(
        CP_UTF8, 0,
        s.data(), (int)s.size(),
        nullptr, 0
    );

    std::wstring ws(len, L'\0');
    MultiByteToWideChar(
        CP_UTF8, 0,
        s.data(), (int)s.size(),
        &ws[0], len
    );

    return ws;
}

std::string
wstring_to_utf8(const std::wstring& ws)
{
    int len = WideCharToMultiByte(
        CP_UTF8, 0,
        ws.data(), (int)ws.size(),
        nullptr, 0,
        nullptr, nullptr
    );

    std::string s(len, '\0');
    WideCharToMultiByte(
        CP_UTF8, 0,
        ws.data(), (int)ws.size(),
        &s[0], len,
        nullptr, nullptr
    );

    return s;
}


void
SleepMS(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

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
    // std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    // return conv.from_bytes(utf8);
    return utf8_to_wstring(utf8);
}

void
PrintWChar(wchar_t c)
{
    // static std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    // std::cout << conv.to_bytes(std::wstring(1, c)); // 转 UTF-8 输出
    std::cout << wstring_to_utf8(std::wstring(1, c));
}


void
SendUnicodeChar(wchar_t c)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;

    input.ki.wScan   = c;
    input.ki.dwFlags = KEYEVENTF_UNICODE;

    SendInput(1, &input, sizeof(INPUT));
}

void
SendVKCode(int c)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;

    input.ki.wVk = c;

    SendInput(1, &input, sizeof(INPUT));
}

bool
GetVKKey(int c)
{
    return (GetKeyState(c) & 0x8000) != 0;
}

void
WaitVKKey(int c)
{
    while(!(GetKeyState(c) & 0x8000));
    while(GetKeyState(c) & 0x8000);
}
