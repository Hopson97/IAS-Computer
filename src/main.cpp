#include <iostream>
#include "IASComputer.h"
#include "IASAssembler.h"

int main(int argc, char** argv)
{
    std::string fileName = "tests/multiply.ias";
    if (argc > 1) {
        fileName = argv[1];
    }
    IASAssembler assembler;
    Memory memory = assembler.assembleFile(fileName.c_str());

    IASComputer computer(memory);
    computer.run();

    std::cout << "\nProgram terminated.\nPress any key to exit.\n";
    std::cin.ignore();std::cin.ignore();

    return 0;
}
