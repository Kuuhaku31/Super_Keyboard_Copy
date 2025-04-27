
#include <conio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>

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
    std::wifstream       file(L"./test.txt"); // �滻Ϊ����ļ�·��
    file.imbue(std::locale(""));              // ʹ���û���Ĭ��locale

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

    std::cout << "����Enter��ʼ��д...\n";
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

    std::cout << "\n==========================================================\n��д����\n";
}

// ��Ӧ��ȡ����
void
MCopy()
{
    std::vector<wchar_t> charArray;
    std::wifstream       file(L"./test.txt"); // �滻Ϊ����ļ�·��
    file.imbue(std::locale(""));              // ʹ���û���Ĭ��locale

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

    std::cout << "����Enter��ʼ��Ӧ��д...\n";
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

    std::cout << "\n==========================================================\n��д����\n";
}

// ��Ҫ����
void
CCopy()
{
    std::vector<wchar_t> charArray;
    std::wifstream       file(L"./test.txt"); // �滻Ϊ����ļ�·��
    file.imbue(std::locale(""));              // ʹ���û���Ĭ��locale

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

    std::cout << "����Enter��ʼ��Ӧ��д...\n";
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

    std::cout << "\n==========================================================\n��д����\n";
}

void
fun_01()
{
    setlocale(LC_ALL, "chs"); // ����localeΪ����(����)

    char i = 0;
    while('q' != i)
    {
        std::cout << "����'N'����ʼ��ȡ\n����'M'����ʼ��Ӧ��ȡ\n����'Q'���˳�...\n";
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

    std::cout << "�������˳�����\n";
}

int
main()
{
    fun_01();
    return 0;
}
