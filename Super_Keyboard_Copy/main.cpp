
#include <windows.h>
#include <winuser.h>

#include <ShlObj.h>
#include <fstream>
#include <vector>
#include <locale>
#include <conio.h>
#include <iostream>

std::wifstream file(L"./test.txt"); // �滻Ϊ����ļ�·��
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
    setlocale(LC_ALL,"chs"); // ����localeΪ����(����)
    file.imbue(std::locale("")); // ʹ���û���Ĭ��locale

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
    
    std::cout<<"����Enter��ʼ��д...\n";
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

    std::cout<<"\n==========================================================\n��д����\n";
}

int
main()
{
    fun_01();
    return 0;
}
