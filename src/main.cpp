#include <iostream>
#include "IASComputer.h"
#include "IASAssembler.h"

int main()
{
    IASAssembler assembler;
    Memory memory = assembler.assembleFile("tests/test1.ias");

    IASComputer computer(memory);
    computer.run();

    return 0;
}
