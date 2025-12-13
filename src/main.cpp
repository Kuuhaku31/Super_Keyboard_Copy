
#include "header.h"

#include <conio.h>
#include <iostream>

int
main()
{
    std::cout << "启动" << std::endl;

    char ch = 0;
    while('q' != ch)
    {
        std::cout << "====================== " << std::endl;
        std::cout << "按下 N 键开始抄写      " << std::endl;
        std::cout << "按下 M 键开始适应抄写  " << std::endl;
        std::cout << "按下 Q 键退出...       " << std::endl;
        std::cout << "====================== " << std::endl;
        std::cout << "抄写期间按下 ESC 停止  " << std::endl;

        ch = _getch();

        std::wstring context = Read("./test.txt");

        switch(ch)
        {
        case 'n':
            Copy(context);
            break;

        case 'm':
            MCopy(context);
            break;

        default: break;
        }
    }

    std::cout << "程序已退出..." << std::endl;
    return 0;
}
