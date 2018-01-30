#include <iostream>
#include "IASComputer.h"
#include "IASAssembler.h"

#include <SFML/Graphics.hpp>

namespace {
    void tryCloseWindow(sf::RenderWindow& window)
    {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }
    }
}

int main(int argc, char** argv)
{
    std::string fileName = "tests/multiply.ias";
    if (argc > 1) {
        fileName = argv[1];
    }
    IASAssembler assembler;
    Memory memory = assembler.assembleFile(fileName.c_str());

    IASComputer computer(memory);

    sf::RenderWindow window({1280, 720}, "8-bit IAS Computer");


    while (window.isOpen()) {

        window.clear();


        window.display();
        tryCloseWindow(window);
    }
    computer.run();





    std::cout << "\nProgram terminated.\nPress any key to exit.\n";
    std::cin.ignore();std::cin.ignore();

    return 0;
}
