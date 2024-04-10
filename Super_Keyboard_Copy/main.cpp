
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

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
SendVKCode(wchar_t c)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_KEYBOARD;

    input.ki.wVk = c;

    SendInput(1, &input, sizeof(INPUT));
}

void
Copy()
{
    std::vector<wchar_t> charArray;
    std::wifstream file(L"./test.txt"); // 替换为你的文件路径
    file.imbue(std::locale("")); // 使用用户的默认locale
    
    if(file.is_open())
    {
        wchar_t c;
        while(file.get(c)) { charArray.push_back(c); }
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
        Sleep(1);
    }

    std::cout<<"\n==========================================================\n抄写结束\n";
                
}

// 适应读取功能
void
MCopy()
{
    std::vector<wchar_t> charArray;
    std::wifstream file(L"./test.txt"); // 替换为你的文件路径
    file.imbue(std::locale("")); // 使用用户的默认locale

    if(file.is_open())
    {
        wchar_t c;
        while(file.get(c)) { charArray.push_back(c); }
        file.close();
    }
    else
    {
        std::cout<<"error\n";
        return;
    }

    std::cout<<"按下Enter开始适应抄写...\n";
    while(!(GetKeyState(VK_RETURN)&0x8000));
    while(GetKeyState(VK_RETURN)&0x8000);
    std::cout<<"==========================================================\n";

    for(wchar_t c : charArray)
    {
        std::wcout<<c;
        SendUnicodeChar(c);
        if((GetKeyState(VK_SPACE)&0x8000)) { break; }
        Sleep(1);

        switch(c)
        {
        case '{':
        case '[':
        case '(':
            SendVKCode(VK_DELETE); 
            break;

        case '\n': 
            SendUnicodeChar(' ');
            SendVKCode(VK_RETURN);
            SendVKCode(VK_HOME);
            break;
        
        default: break;
        }
    }

    std::cout<<"\n==========================================================\n抄写结束\n";

}

void
fun_01()
{
    setlocale(LC_ALL,"chs"); // 设置locale为中文(简体)

    char i = 0;
    while('q'!=i)
    {
        std::cout<<"按下'N'键开始读取\n按下'M'键开始适应读取\n按下'Q'键退出...\n";
        i = 0;
        i = _getch();
        if('n'==i)
        {
            Copy();
        }
        else if('m'==i)
        {
            MCopy();
		}
    }

    std::cout<<"程序已退出：）\n";    
}

int
main()
{
    fun_01();
    return 0;
}
