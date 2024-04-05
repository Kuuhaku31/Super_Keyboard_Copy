#include <windows.h>
#include <winuser.h>

#include <fstream>
#include <vector>
#include <locale>
#include <conio.h>
#include <iostream>

std::wifstream file(L"./test.txt"); // 替换为你的文件路径
std::vector<wchar_t> charArray;

INPUT inputs[4];

bool
Test_for_shift(wchar_t c)
{
    switch(c)
    {
    case '~': case '!': case '@': case '#': case '$': case '%':
    case '^': case '&': case '*': case '(': case ')': case '_':
    case '+': case '{': case '}': case '|': case ':': case '"':
    case '<': case '>': case '?': return true;
    default: return isupper(c);
    }
}

void
SendASCIIChar(wchar_t c)
{
    inputs[2].ki.wVk = inputs[3].ki.wVk = VkKeyScan(c);
    if(Test_for_shift(c))
    {
        SendInput(1, &inputs[0], sizeof(INPUT));
        SendInput(1, &inputs[2], sizeof(INPUT));
        SendInput(1, &inputs[3], sizeof(INPUT));
        SendInput(1, &inputs[1], sizeof(INPUT));
    }
    else
    {
        SendInput(1, &inputs[2], sizeof(INPUT));
        SendInput(1, &inputs[3], sizeof(INPUT));
    }
}

void
SendUnicodeChar(wchar_t c)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = c;
    input.ki.dwFlags = KEYEVENTF_UNICODE;
    SendInput(1, &input, sizeof(INPUT));
}


void
fun_01()
{
    file.imbue(std::locale("")); // 使用用户的默认locale
    if(file.is_open())
    {
        wchar_t c;
        while (file.get(c)) { charArray.push_back(c); }
        file.close();

        ZeroMemory(inputs, sizeof(inputs));
        for(int i = 0; i<4; i++) { inputs[i].type = INPUT_KEYBOARD; }
        inputs[1].ki.dwFlags = inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
        inputs[0].ki.wVk = inputs[1].ki.wVk = VK_SHIFT;
    }
    else
    {
        std::wcout<<L"error"<<std::endl;
        return;
    }
    
    std::cout<<"按下Enter开始..."<<std::endl;

    while(!(GetAsyncKeyState(VK_RETURN)&0x8000));

    for(wchar_t c : charArray)
    {
        std::wcout<<c;
        if(iswascii(c))
        {
            SendASCIIChar(c);
        }
        else
        {
            SendUnicodeChar(c);
        }
        if(GetAsyncKeyState(VK_RETURN)&0x8000) { break; }
        Sleep(30);
    }

    std::cout<<"结束"<<std::endl;
}

int
main()
{
    fun_01();
    return 0;
}
