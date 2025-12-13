
#include "header.h"

#include <codecvt>
#include <fstream>
#include <locale>
#include <iostream>

#define LINE "=========================================================="
#define SLEEP_MS 1

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

void
print_wchar(wchar_t c)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::cout << conv.to_bytes(std::wstring(1, c));  // 转 UTF-8 输出
}

void
begin()
{
    std::cout << "按下 Enter 开始抄写..." << std::endl;
    WaitVKKey(VK_RETURN);
    std::cout << LINE << std::endl;
}

bool
interrupt()
{
    if(GetVKKey(VK_ESCAPE))
    {
        std::cout << std::endl << "== 中断抄写 ==" << std::endl;
        return true;
    }
    else return false;
}

void
end()
{
    std::cout << LINE << std::endl << "抄写结束" << std::endl;
}


void
Copy(std::wstring context)
{
    begin();
    for(wchar_t c : context)
    {
        print_wchar(c);
        switch(c)
        {
        case '\n':  SendVKCode(VK_RETURN);  break;
        case '\t':  SendVKCode(VK_TAB);     break;
        default:    SendUnicodeChar(c);     break;
        }
        if(interrupt()) break;
        Sleep(SLEEP_MS);
    }
    end();
}

void
MCopy(std::wstring context)
{
    begin();
    for(wchar_t c : context)
    {
        print_wchar(c);

        switch(c)
        {
        case '{':
        case '[':
        case '(':
            SendUnicodeChar(c);
            SendVKCode(VK_DELETE);
            break;

        case '\n':
            SendUnicodeChar(' ');
            SendVKCode(VK_RETURN);
            SendVKCode(VK_HOME);
            break;

        default:
            SendUnicodeChar(c);
            break;
        }
        if(interrupt()) break;
        Sleep(SLEEP_MS);
    }
    end();
}
