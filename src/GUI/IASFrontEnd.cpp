#include "IASFrontEnd.h"

#include <sstream>
#include <iomanip>
#include <bitset>
#include <thread>
#include <chrono>
#include <iostream>


std::string getDecAndBinString(Word value)
{
    std::ostringstream stream;
    stream << std::setw(4) << (int)value << " " << std::bitset<8>(value);
    return stream.str();
}


IASFrontEnd::IASFrontEnd(const Memory& memory)
:   m_window        ({1280, 720}, "8-bit IAS Computer")
,   m_iasComputer   (memory)
{
    m_window.setFramerateLimit(30);
    m_mainFont.loadFromFile("res/Anonymous.ttf");

    initRegisterDisplay();
    initInstructionDisplay();

    m_memorySect.init("Memory", {MEM_GUI_X - 15, MEM_GUI_Y - 25}, {720, 430}, m_mainFont);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 4; x++) {
            m_memoryCells.emplace_back(x * 8 + y,
                                       x * MemoryCell::XSIZE + MEM_GUI_X + x * 15,
                                       y * MemoryCell::YSIZE + MEM_GUI_Y + y * 5,
                                       m_mainFont);
        }
    }
    updateMemoryDisplay();

    m_sectionIO.init("User Input and Output", {IO_GUI_X, IO_GUI_Y}, {460, 300}, m_mainFont);
}

//Runs the computer, either using CLI or GUI
void IASFrontEnd::run(bool useGui)
{
    if (useGui) {
        int ticks = 0;
        sf::Clock c;
        while (m_window.isOpen()) {
            m_window.clear();

            //Cycle every n seconds, updates display in process
            if (c.getElapsedTime() > sf::seconds(m_tickDelay)) {
                if (ticks % 2 == 0) {
                    cycleComputer();
                } else {
                    updateDisplays();
                }
                c.restart();
                ticks++;
            }
            render();

            m_window.display();
            tryCloseWindow();
            if (m_iasComputer.getOpcodeFromInstr() == INSTRUCTION_END) break;
        }
    }
    else {
        m_window.close();
        m_iasComputer.run();
    }
    m_window.close();
}

//Does 1 fetch-execute cycle
void IASFrontEnd::cycleComputer()
{
    m_iasComputer.fetch();
    updateRegisterDisplay();
    updateInstructionDisplay();
    updateMemoryDisplay();
    m_iasComputer.execute();
}

//Check if user has closed window
void IASFrontEnd::tryCloseWindow()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (e.type == sf::Event::KeyReleased) {
            auto code = e.key.code;
            if (code == sf::Keyboard::Left) {
                m_tickDelay -= 0.1;
                if (m_tickDelay <= 0) m_tickDelay = 0;
                std::cout << m_tickDelay << "\n";
            }
            else if (code == sf::Keyboard::Right) {
                m_tickDelay += 0.1;
                std::cout << m_tickDelay << "\n";
            }
        }
    }
}

void IASFrontEnd::updateDisplays()
{
    updateRegisterDisplay();
    updateInstructionDisplay();
    updateMemoryDisplay();
}


//Updates the values of the register displays to those stored in the IAS computer
void IASFrontEnd::updateRegisterDisplay()
{
    auto* start = m_iasComputer.getFirstRegister(); //Get pointer to first register

    for (int i = 0; i < NUM_REGISTERS; i++) {
        Word value = *(start + i);  //Offset pointer by "i", to find correct value
        m_registerDisplay[i].update(value);
    }
}

void IASFrontEnd::updateInstructionDisplay()
{
    Word opcode         = m_iasComputer.getOpcodeFromInstr();
    Word address        = m_iasComputer.getMemAddrFromInstr();

    m_instructionDisplay[0].update(opcode);
    m_instructionDisplay[1].update(address);
    m_instructionDisplay[2].update(opcodeString.at(opcode));
}

//Updates the values stored at the memory addresses
void IASFrontEnd::updateMemoryDisplay()
{
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 4; x++) {
            m_memoryCells[y * 4 + x].update(m_iasComputer.getMemory()[x * 8 + y],
                                            m_iasComputer.getAddressRegister());
        }
    }
}

//Renders the displays
void IASFrontEnd::render()
{
    m_memorySect        .draw(m_window);
    m_registerSect      .draw(m_window);
    m_instructionSect   .draw(m_window);
    m_sectionIO         .draw(m_window);

    for (auto& regDisplay : m_registerDisplay) {
        regDisplay.draw(m_window);
    }

    for (auto& instrDisp : m_instructionDisplay) {
        instrDisp.draw(m_window);
    }

    for (auto& memoryCell : m_memoryCells) {
        memoryCell.draw(m_window);
    }
}

/*
    Some functions to initilise the different sections of the user interface
*/
void IASFrontEnd::initRegisterDisplay()
{
    m_registerDisplay.emplace_back(m_mainFont, "   Accumulator Register: ", 260);
    m_registerDisplay.emplace_back(m_mainFont, " Memory Buffer Register: ", 260);
    m_registerDisplay.emplace_back(m_mainFont, "   Instruction Register: ", 260);
    m_registerDisplay.emplace_back(m_mainFont, "Memory Address Register: ", 260);
    m_registerDisplay.emplace_back(m_mainFont, "        Program Counter: ", 260);
    m_registerDisplay.emplace_back(m_mainFont, "    IO Address Register: ", 260);
    m_registerDisplay.emplace_back(m_mainFont, "     IO Buffer Register: ", 260);

    for (int y = 0; y < NUM_REGISTERS; y++) {
        float yPosition = REG_GUI_Y + 20 + y * TEXT_HEIGHT;
        m_registerDisplay[y].moveText(REG_GUI_X, yPosition);
    }

    m_registerSect.init("Registers", {REG_GUI_X, REG_GUI_Y}, {460, 230}, m_mainFont);
}

void IASFrontEnd::initInstructionDisplay()
{
    m_instructionDisplay.emplace_back(m_mainFont, "     Opcode: ", 125);
    m_instructionDisplay.emplace_back(m_mainFont, "    Address: ", 125);
    m_instructionDisplay.emplace_back(m_mainFont, "Description: ", 125);

    for (int i = 0; i < 3; i++) {
        m_instructionDisplay[i].moveText(INS_GUI_X, INS_GUI_Y + 20 + i * TEXT_HEIGHT);
    }
    m_instructionSect.init("Opcode and Address", {INS_GUI_X, INS_GUI_Y}, {1000, 130}, m_mainFont);
}

