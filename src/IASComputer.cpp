#include "IASComputer.h"

#include <iostream>
#include <bitset>

constexpr uint8_t OPCODE_BITS   = 3;
constexpr uint8_t MEMORY_BITS   = 5;

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
        std::cout << "Opcode: " << (int)opcode << " unknown\n";
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
    m_memory.at(address) = m_accumulator;
}

void IASComputer::load()
{
    m_accumulator = getValueStoredAtInstrAddress();
}

//TODO use I/O registers?
void IASComputer::input()
{
    std::cout << "Please input a value: ";
    std::cin >> m_accumulator;
}

//TODO use I/O registers?
void IASComputer::output()
{
    std::cout << "Output: " << (int)m_accumulator << "\n";
}

void IASComputer::jumpIfPos()
{
    if (m_accumulator > 0) {
        m_programCounter = getValueStoredAtInstrAddress();
    }
}

void IASComputer::printOpcodeAndAddress()
{
    std::cout   << std::bitset<8>(getOpcodeFromInstr()) << " "
                << std::bitset<8>(getMemAddrFromInstr())
                << "\n";
}

//Extracts the memory address from the instruction register
uint8_t IASComputer::getMemAddrFromInstr()
{
    uint8_t address = m_instructionRegister << OPCODE_BITS;
    return address >> OPCODE_BITS;
}

//Extracts the opcode address from the instruction register
uint8_t IASComputer::getOpcodeFromInstr()
{
    return m_instructionRegister >> MEMORY_BITS;
}

//Extracts the memory address from the instruction register
//and gets the value stored there
uint8_t IASComputer::getValueStoredAtInstrAddress()
{
    return m_memory.at(getMemAddrFromInstr());
}



