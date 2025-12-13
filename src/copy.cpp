
#include "header.h"

#include <iostream>

#define LINE "=========================================================="
#define SLEEP_MS 1


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
    if(GetVKKey(VK_SPACE))
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
        PrintWChar(c);
        switch(c)
        {
        case '\n':  SendVKCode(VK_RETURN);  break;
        case '\t':  SendVKCode(VK_TAB);     break;
        default:    SendUnicodeChar(c);     break;
        }
        if(interrupt()) break;
        SleepMS(SLEEP_MS);
    }
    end();
}

void
MCopy(std::wstring context)
{
    begin();
    for(wchar_t c : context)
    {
        PrintWChar(c);

        switch(c)
        {
        case '{':
        case '[':
        case '(':
            SendUnicodeChar(c);
            SendVKCode(VK_DELETE);
            break;

        case '\n':
            SendVKCode(VK_ESCAPE);
            SendVKCode(VK_RETURN);
            SendVKCode(VK_HOME);
            break;

        case '\t':
            SendVKCode(VK_ESCAPE);
            SendVKCode(VK_TAB);
            break;

        default:
            SendUnicodeChar(c);
            break;
        }
        if(interrupt()) break;
        SleepMS(SLEEP_MS);
    }
    end();
}
