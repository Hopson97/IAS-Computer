#include <iostream>
#include "IASComputer.h"

int main()
{
    Memory memory;
    memory.fill(0b0111'01011);
    IASComputer computer(memory);
    computer.run();

    return 0;
}
