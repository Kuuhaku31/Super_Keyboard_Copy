#include <windows.h>
#include <winuser.h>

#include <fstream>
#include <vector>

#include <iostream>

std::ifstream file("./test.txt"); // 替换为你的文件路径
std::vector<char> charArray;

INPUT inputs[4];

bool
Test_for_shift(char c)
{
    switch (c)
    {
    case '~': return true;
    case '!': return true;
    case '@': return true;
    case '#': return true;
    case '$': return true;
    case '%': return true;
    case '^': return true;
    case '&': return true;
    case '*': return true;
    case '(': return true;
    case ')': return true;
    case '_': return true;
    case '+': return true;

    case '{': return true;
    case '}': return true;
    case '|': return true;

    case ':': return true;
    case '"': return true;

    case '<': return true;
    case '>': return true;
    case '?': return true;

    default: return false;
    }
}

void 
SendKeyInput(char c)
{
    inputs[2].ki.wVk = inputs[3].ki.wVk = VkKeyScan(c);
    if (Test_for_shift(c))
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
fun_01()
{
    if (file.is_open()) 
    {
        char c;
        while (file.get(c)) { charArray.push_back(c); }
        file.close();

        ZeroMemory(inputs, sizeof(inputs));
        for (int i = 0; i < 4; i++) { inputs[i].type = INPUT_KEYBOARD; }
        inputs[2].ki.dwFlags = inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
        inputs[0].ki.wVk = inputs[1].ki.wVk = VK_SHIFT;

        std::cout << "ok" << std::endl;

        Sleep(3000);

        for (char c : charArray)
        {
            SendKeyInput(c);
            Sleep(30);
        }
    }
    else
    {
        std::cout << "error" << std::endl;
    }
}

void
fun_02()
{
    Sleep(3000);

    // 模拟鼠标左键点击
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

    // 模拟键盘输入
    keybd_event('A', 0, 0, 0); // 按下 'A'
    keybd_event('A', 0, KEYEVENTF_KEYUP, 0); // 释放 'A'
}

void
Super_print(char c)
{
    keybd_event(c, 0, 0, 0); // 按下 c
    keybd_event(c, 0, KEYEVENTF_KEYUP, 0); // 释放 c
}

int
main()
{
    fun_01();

    return 0;
}
