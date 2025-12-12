
#include <conio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>

void
Copy()
{
    std::vector<wchar_t> charArray;
    std::wifstream       file(L"./test.txt"); // 替换为你的文件路径
    try
    {
        file.imbue(std::locale("")); // 尝试使用用户的默认 locale
    }
    catch(const std::runtime_error&)
    {
        // 在部分 MinGW/Windows 环境下，std::locale("") 可能无效，回退到可用的经典 locale
        file.imbue(std::locale::classic());
    }

    if(file.is_open())
    {
        wchar_t c;
        while(file.get(c))
        {
            charArray.push_back(c);
        }
        file.close();
    }
    else
    {
        std::cout << "error\n";
        return;
    }

    std::cout << "按下Enter开始抄写...\n";
    while(!(GetKeyState(VK_RETURN) & 0x8000));
    while(GetKeyState(VK_RETURN) & 0x8000);
    std::cout << "==========================================================\n";

    for(wchar_t c : charArray)
    {
        std::wcout << c;

        switch(c)
        {
        case '\n':
            SendVKCode(VK_RETURN);
            break;
        case '\t':
            SendVKCode(VK_TAB);
            break;
        default:
            SendUnicodeChar(c);
            break;
        }

        if((GetKeyState(VK_SPACE) & 0x8000))
        {
            break;
        }
        Sleep(1);
    }

    std::cout << "\n==========================================================\n抄写结束\n";
}

// 适应读取功能
void
MCopy()
{
    std::vector<wchar_t> charArray;
    std::wifstream       file(L"./test.txt"); // 替换为你的文件路径
    try
    {
        file.imbue(std::locale("")); // 尝试使用用户的默认 locale
    }
    catch(const std::runtime_error&)
    {
        file.imbue(std::locale::classic());
    }

    if(file.is_open())
    {
        wchar_t c;
        while(file.get(c))
        {
            charArray.push_back(c);
        }
        file.close();
    }
    else
    {
        std::cout << "error\n";
        return;
    }

    std::cout << "按下Enter开始适应抄写...\n";
    while(!(GetKeyState(VK_RETURN) & 0x8000));
    while(GetKeyState(VK_RETURN) & 0x8000);
    std::cout << "==========================================================\n";

    for(wchar_t c : charArray)
    {
        std::wcout << c;

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

        if((GetKeyState(VK_SPACE) & 0x8000))
        {
            break;
        }
        Sleep(1);
    }

    std::cout << "\n==========================================================\n抄写结束\n";
}

// 不要换行
void
CCopy()
{
    std::vector<wchar_t> charArray;
    std::wifstream       file(L"./test.txt"); // 替换为你的文件路径
    try
    {
        file.imbue(std::locale("")); // 尝试使用用户的默认 locale
    }
    catch(const std::runtime_error&)
    {
        file.imbue(std::locale::classic());
    }

    if(file.is_open())
    {
        wchar_t c;
        while(file.get(c))
        {
            charArray.push_back(c);
        }
        file.close();
    }
    else
    {
        std::cout << "error\n";
        return;
    }

    std::cout << "按下Enter开始适应抄写...\n";
    while(!(GetKeyState(VK_RETURN) & 0x8000));
    while(GetKeyState(VK_RETURN) & 0x8000);
    std::cout << "==========================================================\n";

    bool is_space = true;
    bool is_in    = false;
    for(wchar_t c : charArray)
    {
        std::wcout << c;

        switch(c)
        {
        case '#':
            is_in = true;
            SendVKCode(VK_RETURN);
            SendVKCode(VK_HOME);
            SendUnicodeChar(c);
            break;

        case '\n':
            if(is_in)
            {
                is_in = false;
                SendVKCode(VK_RETURN);
                SendVKCode(VK_HOME);
            }
            break;

        case ' ':
            if(is_space)
            {
                is_space = false;
                SendUnicodeChar(c);
            }
            break;

        default:
            is_space = true;
            SendUnicodeChar(c);
            break;
        }

        if((GetKeyState(VK_SPACE) & 0x8000))
        {
            break;
        }
        Sleep(1);
    }

    std::cout << "\n==========================================================\n抄写结束\n";
}

int
main()
{
    std::cout << "start" << std::endl;
    setlocale(LC_ALL, "chs"); // 设置locale为中文(简体)

    char i = 0;
    while('q' != i)
    {
        std::cout << "按下'N'键开始读取\n按下'M'键开始适应读取\n按下'Q'键退出...\n";
        i = 0;
        i = _getch();

        switch(i)
        {
        case 'n':
            Copy();
            break;

        case 'm':
            MCopy();
            break;

        case 'c':
            CCopy();
            break;

        default:
            break;
        }
    }

    std::cout << "程序已退出..." << std::endl;

    return 0;
}
