#include "IASComputer.h"

#include <iostream>

constexpr uint8_t OP_CODE_BITS = 3;
constexpr uint8_t MEMORY_BITS  = 5;

IASComputer::IASComputer(const Memory& memory)
:   m_memory        (memory)
,   m_commandMap {
        {0, std::bind(IASComputer::add, this)},
        {1, std::bind(IASComputer::subtract, this)},
    }
{ }

void IASComputer::run()
{
    while (true) {
        if (m_programCounter == m_memory.size()){
            break;
        }
        fetch();
        execute();
    }
}

void IASComputer::fetch()
{
    m_memAddressRegister    = m_programCounter++;
    m_memBufferRegister     = m_memory[m_memAddressRegister];
    m_instructionRegister   = m_memBufferRegister;
}

void IASComputer::execute()
{
    uint8_t opcode = m_instructionRegister >> MEMORY_BITS;
    try {
        m_commandMap.at(opcode)();
    }
    catch (std::out_of_range& e) {
        std::cout << (int)opcode << " unknown\n";
    }

}

void IASComputer::add()
{
    std::cout << "adding\n";
}

void IASComputer::subtract()
{

}

void IASComputer::store()
{

}

void IASComputer::load()
{

}
