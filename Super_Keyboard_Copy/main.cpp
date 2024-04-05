
#include <windows.h>
#include <winuser.h>

#include <ShlObj.h>
#include <fstream>
#include <vector>
#include <locale>
#include <conio.h>
#include <iostream>

std::wifstream file(L"./test.txt"); // 替换为你的文件路径
std::vector<wchar_t> charArray;

void 
SendUnicodeChar(wchar_t c)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;

    if('\n'==c)
    {
        input.ki.wVk = VK_RETURN;
    }
    else if('\t'==c)
    {
        input.ki.wVk = VK_TAB;
    }
    else
    {
        input.ki.wScan = c;
        input.ki.dwFlags = KEYEVENTF_UNICODE;
    }

    SendInput(1, &input, sizeof(INPUT));
}

void
fun_01()
{
    setlocale(LC_ALL,"chs"); // 设置locale为中文(简体)
    file.imbue(std::locale("")); // 使用用户的默认locale

    if(file.is_open())
    {
        wchar_t c;
        while (file.get(c)) { charArray.push_back(c); }
        file.close();
    }
    else
    {
        std::cout<<"error\n";
        return;
    }
    
    std::cout<<"按下Enter开始抄写...\n";
    while(!(GetKeyState(VK_RETURN)&0x8000));
    while(GetKeyState(VK_RETURN)&0x8000);
    std::cout<<"==========================================================\n";

    for(wchar_t c : charArray)
    {
        std::wcout<<c;
        SendUnicodeChar(c);
        if((GetKeyState(VK_SPACE)&0x8000)) { break; }
        Sleep(30);
    }

    std::cout<<"\n==========================================================\n抄写结束\n";
}

int
main()
{
    fun_01();
    return 0;
}
