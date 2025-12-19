
#include "color_io.h"
#include "header.h"


#include <conio.h>
#include <iostream>
#include <string>

int
main(int argc, char* argv[])
{
    std::string filename = "";

    if(argc < 2)
    {
        PrintLog(LABEL, "用法: %s <filename>", argv[0]);
        return 0;
    }
    else
    {
        filename = std::string(argv[1]);
        PrintLog(LABEL, "Super Keyboard Copyer 启动");
    }

    std::string  input   = "";
    std::wstring context = L"";
    while(true)
    {
        std::cout << "> ======================= " << std::endl;
        std::cout << "> 当前文件: " << filename << std::endl;
        std::cout << "> ======================= " << std::endl;
        std::cout << "> n 开始抄写              " << std::endl;
        std::cout << "> m 开始适应抄写          " << std::endl;
        std::cout << "> f 更换读取文件          " << std::endl;
        std::cout << "> exit 退出...            " << std::endl;
        std::cout << "> ======================= " << std::endl;
        std::cout << "> 抄写期间按下 SPACE 停止 " << std::endl;
        std::cout << "> ======================= " << std::endl;

        GetInput(LABEL, input);
        if(input == "exit") break;
        if(input == "f")
        {
            GetInput(LABEL_NEW_FILE, filename);
            std::cout << "> 读取文件: " << filename << std::endl;
            continue;
        }

        SleepMS(500); // 等待半秒
        context = Read(filename);
        if(input == "n")
            Copy(context);
        else if(input == "m")
            MCopy(context);
    }

    PrintLog(LABEL, "程序已退出...");
    return 0;
}
