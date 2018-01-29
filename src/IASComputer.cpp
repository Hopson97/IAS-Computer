#include "IASComputer.h"

#include <iostream>
#include <iomanip>
#include <bitset>

#include "Colour.h"

//#define PRINT_STATE

IASComputer::IASComputer(const Memory& memory)
:   m_memory        (memory)
,   m_commandMap {
        //Bind op-codes to member functions
        {0, std::bind(IASComputer::add,         this)},
        {1, std::bind(IASComputer::subtract,    this)},
        {2, std::bind(IASComputer::store,       this)},
        {3, std::bind(IASComputer::load,        this)},
        {4, std::bind(IASComputer::input,       this)},
        {5, std::bind(IASComputer::output,      this)},
        {6, std::bind(IASComputer::jumpIfPos,   this)},
    }
{
    m_memory[31] = 1;
}

//Handles the fetch and execute cycle
void IASComputer::run()
{
    while (true) {
        std::cout << TextColour::Green << "\n ========= A new cycle begins =========\n" << TextColour::DarkGrey;
        if ((int)m_programCounter == (int)m_memory.size()) {
            break;
        }
        fetch();
        //Test for end of instructions
        if (getOpcodeFromInstr() == END_OF_FILE) {
            break;
        }
        execute();
    }
}

//Fetches the next instruction from memory
void IASComputer::fetch()
{
    m_memAddressRegister    = m_programCounter++;
    printFullState();
    m_memBufferRegister     = m_memory[m_memAddressRegister];
    printFullState();
    m_instructionRegister   = m_memBufferRegister;
    printFullState();
}


//Executes next instruction
void IASComputer::execute()
{
    Word opcode = getOpcodeFromInstr();
    try {
        m_commandMap.at(opcode)();
    }
    catch (std::out_of_range& e) {
        std::cout << TextColour::DarkRed << "Opcode: " << (int)opcode << " unknown\n" << TextColour::DarkGrey;
    }
    std::cout << "Program counter: " << (int)m_programCounter << "\n";
}

//Bunch of functions for the op-codes
void IASComputer::add()
{
    m_accumulator += getValueStoredAtInstrAddress();
}

void IASComputer::subtract()
{
    m_accumulator -= getValueStoredAtInstrAddress();
}

void IASComputer::store()
{
    auto address = getMemAddrFromInstr();
    m_memory.at(address) = m_accumulator;
}

void IASComputer::load()
{
    //std::cout << TextColour::Red <<"LOAD before " << (int)getValueStoredAtInstrAddress() << "\n";
    m_accumulator = getValueStoredAtInstrAddress();
}

//TODO use I/O registers?
void IASComputer::input()
{
    std::cout << TextColour::Cyan << "Please input a value: " << TextColour::DarkGrey;
    std::cin  >> m_accumulator;
}

//TODO use I/O registers?
void IASComputer::output()
{
    std::cout   << TextColour::Cyan << "Output: "
                << TextColour::DarkGrey << (int)m_accumulator << "\n";
}

void IASComputer::jumpIfPos()
{
    if (m_accumulator > 0) {
        auto address = getMemAddrFromInstr();
        m_programCounter = (RegType)address;
    }
}

void IASComputer::printOpcodeAndAddress()
{
    int op = (int)getOpcodeFromInstr();
    int ad = (int)getMemAddrFromInstr();

    std::cout   << "Opcode:  " << std::setw(4) << op << " " << std::bitset<8>(op) << "\n"
                << "Address: " << std::setw(4) << ad << " " << std::bitset<8>(ad)
                << "\n";
}

//Extracts the memory address from the instruction register
Word IASComputer::getMemAddrFromInstr() const
{
    Word address = (Word)m_instructionRegister & 0x1F;
    std::cout   << "Address shift 1 and 2\n"
                << std::bitset<8>(m_instructionRegister) << " " << std::bitset<8>(address) << " " << (int)address << "\n";
    return address;
}

//Extracts the opcode address from the instruction register
Word IASComputer::getOpcodeFromInstr() const
{
    return m_instructionRegister >> MEMORY_BITS;
}

//Extracts the memory address from the instruction register
//and gets the value stored there
Word IASComputer::getValueStoredAtInstrAddress() const
{
    return m_memory.at(getMemAddrFromInstr());
}

void IASComputer::printFullState()
{
    #ifdef PRINT_STATE
    std::cout   << "\n"
                << "\nAccumulator Register      " << std::setw(4) << m_accumulator          << " " << std::bitset<16>(m_accumulator)
                << "\nMemory Buffer  Register:  " << std::setw(4) << m_memBufferRegister    << " " << std::bitset<8>(m_memBufferRegister)
                << "\nMemory Address Register:  " << std::setw(4) << m_memAddressRegister   << " " << std::bitset<8>(m_memAddressRegister)
                << "\nInstruction Register:     " << std::setw(4) << m_instructionRegister  << " " << std::bitset<8>(m_instructionRegister)
                << "\nProgram Counter Register: " << std::setw(4) << m_programCounter       << " " << std::bitset<8>(m_programCounter)
                << "\n";
    #endif // PRINT_STATE
}




















