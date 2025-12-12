
#include "utf_reader.h"

int
main()
{
    printf("Hello, Test02!\n");

    std::string utf8;
    std::string enc, err;
    if(read_file_to_utf8("D:\\repositories\\Super_Keyboard_Copy\\out\\test.txt", utf8, &enc, &err))
    {
        std::cout << "Detected encoding: " << enc << "\n";
        std::cout << "Content (UTF-8):\n"
                  << utf8;
    }
    else
    {
        std::cerr << "Failed to read file: " << err << "\n";
    }
    return 0;
}
