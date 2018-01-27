#include "IASComputer.h"

#include <iostream>
#include <bitset>

constexpr uint8_t OPCODE_BITS = 3;
constexpr uint8_t MEMORY_BITS  = 5;

IASComputer::IASComputer(const Memory& memory)
:   m_memory        (memory)
,   m_commandMap {
        {0, std::bind(IASComputer::add,         this)},
        {1, std::bind(IASComputer::subtract,    this)},
        {2, std::bind(IASComputer::store,       this)},
        {3, std::bind(IASComputer::load,        this)},
        {4, std::bind(IASComputer::input,       this)},
        {5, std::bind(IASComputer::output,      this)},
        {6, std::bind(IASComputer::jumpIfPos,   this)},
    }
{ }

void IASComputer::run()
{
    while (true) {
        if ((int)m_programCounter == (int)m_memory.size()) {
            break;
        }
        fetch();
        execute();
    }
}

//Fetches the next instruction from memory
void IASComputer::fetch()
{
    m_memAddressRegister    = m_programCounter++;
    m_memBufferRegister     = m_memory[m_memAddressRegister];
    m_instructionRegister   = m_memBufferRegister;
}

//Executes next instruction
void IASComputer::execute()
{
    uint8_t opcode = getOpcodeFromInstr();
    try {
        m_commandMap.at(opcode)();
    }
    catch (std::out_of_range& e) {
        std::cout << (int)opcode << " unknown\n";
    }
}

//Commands
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
}

void IASComputer::load()
{
    m_accumulator = getValueStoredAtInstrAddress();
}

void IASComputer::input()
{

}

void IASComputer::output()
{

}

void IASComputer::jumpIfPos()
{
     auto address = getMemAddrFromInstr();
}

void IASComputer::printOpcodeAndAddress()
{
    std::cout   << std::bitset<8>(getOpcodeFromInstr()) << " "
                << std::bitset<8>(getMemAddrFromInstr())
                << "\n";
}

//Extracts the memory address from
uint8_t IASComputer::getMemAddrFromInstr()
{
    uint8_t address = m_instructionRegister << OPCODE_BITS;
    return address >> OPCODE_BITS;
}

uint8_t IASComputer::getOpcodeFromInstr()
{
    return m_instructionRegister >> MEMORY_BITS;
}

uint8_t IASComputer::getValueStoredAtInstrAddress()
{
    return m_memory.at(getMemAddrFromInstr());
}



