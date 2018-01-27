#include <iostream>
#include "IASComputer.h"

int main()
{
    Memory memory;
    memory.fill(0);
    IASComputer computer(memory);
    computer.run();

    return 0;
}
