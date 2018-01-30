#include <iostream>
#include "IASFrontEnd.h"
#include "IASAssembler.h"

int main(int argc, char** argv)
{
    std::string fileName = "tests/multiply.ias";
    if (argc > 1) {
        fileName = argv[1];
    }

    Memory memory = IASAssembler().assembleFile(fileName.c_str());
    IASFrontEnd app(memory);
    app.run();

    std::cout << "\nProgram terminated.\nPress any key to exit.\n";
    std::cin.ignore();std::cin.ignore();

    return 0;
}
