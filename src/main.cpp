#include <iostream>
#include "IASComputer.h"

int main()
{
    Memory memory;
    memory.fill(0);
    memory[0] = 0b100'00000;
    memory[1] = 0b010'10000;
    memory[2] = 0b100'00000;
    memory[3] = 0b000'10000;
    memory[4] = 0b101'00000;

    IASComputer computer(memory);
    computer.run();

    return 0;
}
