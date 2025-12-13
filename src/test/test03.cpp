
#include "header.h"
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string>
#include <codecvt>
#include <locale>

int
main()
{
    printf("Hello, Test03!\n");

    // sheep
    for(int i = 0; i < 3; i++)
    {
        printf("Sheep %d\n", i + 1);
        std::clock_t start_time = std::clock();
        while((std::clock() - start_time) / CLOCKS_PER_SEC < 1);
    }

    std::wstring str2 = Read("./test.txt");

    for(wchar_t c : str2)
    {
        // print_wchar(c);
        if(c == L'\n') SendVKCode(VK_RETURN); 
        else SendUnicodeChar(c);
        Sleep(5);
    }

    return 0;
}
