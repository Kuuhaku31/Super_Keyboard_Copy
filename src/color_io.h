
#pragma once

#include <stdarg.h>
#include <iostream>

inline
void
PrintLog(const char* label, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    printf("[%s]: ", label);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

inline
void
GetInput(const char* label, std::string& input_buffer)
{
    // 提示用户输入姓名
    printf("[%s]: ", label);
    std::getline(std::cin, input_buffer);

    // 去除输入末尾的换行符
    for(size_t i = 0; i < input_buffer.size(); ++i)
    {
        if(input_buffer[i] == '\n' || input_buffer[i] == '\r')
        {
            input_buffer.erase(i);
            break;
        }
    }
}
