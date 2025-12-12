
#include "header.h"
#include <ctime>
#include <stdio.h>
#include <windows.h>

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

    SendUnicodeChar(L'你');
    SendUnicodeChar(L'好');
    SendVKCode(VK_RETURN);
    SendUnicodeChar(L'你');
    SendUnicodeChar(L'好');
    SendVKCode(VK_RETURN);
    SendUnicodeChar(L'世');
    SendUnicodeChar(L'界');

    return 0;
}
