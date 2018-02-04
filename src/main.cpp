#include <iostream>
#include "GUI/IASFrontEnd.h"
#include "IASAssembler.h"

struct Test
{
    int x = 10;
    int y = 5;
};

int main(int argc, char** argv)
{
    std::string fileName = "tests/add.ias";
    if (argc > 1) {
        fileName = argv[1];
    }

    Memory memory = IASAssembler().assembleFile(fileName.c_str());
    IASFrontEnd app(memory);
    app.run(true);

    std::cout << "\nProgram terminated.\nPress any key to exit.\n";
    std::cin.ignore();std::cin.ignore();

    return 0;
}
