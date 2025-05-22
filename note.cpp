
#include <windows.h>
#include <winuser.h>

#include <ShlObj.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>


bool
Test_for_shift(wchar_t c)
{
    switch(c)
    {
    case '~':
    case '!':
    case '@':
    case '#':
    case '$':
    case '%':
    case '^':
    case '&':
    case '*':
    case '(':
    case ')':
    case '_':
    case '+':
    case '{':
    case '}':
    case '|':
    case ':':
    case '"':
    case '<':
    case '>':
    case '?': return true;
    default: return isupper(c);
    }
}

void
SendASCIIChar(wchar_t c)
{
    INPUT inputs[4];

    ZeroMemory(inputs, sizeof(inputs));
    for(int i = 0; i < 4; i++)
    {
        inputs[i].type = INPUT_KEYBOARD;
    }
    inputs[1].ki.dwFlags = inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[0].ki.wVk = inputs[1].ki.wVk = VK_SHIFT;

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


bool
init()
{
    wchar_t    path_ch[4096];
    BROWSEINFO bInfo = { 0 };
    bInfo.hwndOwner  = GetForegroundWindow(); // 父窗口
    bInfo.lpszTitle  = TEXT("Browse File Folder");
    bInfo.ulFlags    = BIF_RETURNONLYFSDIRS | BIF_USENEWUI /*包含一个编辑框 用户可以手动填写路径 对话框可以调整大小之类的..*/ |
                    BIF_UAHINT /*带TIPS提示*/;
    LPITEMIDLIST lpDlist;
    lpDlist = SHBrowseForFolder(&bInfo);
    if(lpDlist != NULL)
    {
        SHGetPathFromIDListA(lpDlist, reinterpret_cast<LPSTR>(path_ch));
        // file.open(path_ch);
        return true;
    }
    else
    {
        return false;
    }
}
