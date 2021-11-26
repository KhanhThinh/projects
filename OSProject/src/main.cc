#include <stdint.h>
#include "Console.cc"
#include "Program.cc"

int main(void)
{
    srand((int)time(0));
    Program fs;
    fs.run();
    return 0;
}