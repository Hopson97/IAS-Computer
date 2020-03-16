#include "IASComputer.h"

#include <bitset>
#include <iomanip>
#include <iostream>

IASComputer::IASComputer(const Memory &memory)
    : m_memory(memory)
    , m_commandMap{
          // Bind op-codes to member functions
          {0, std::bind(&IASComputer::add, this)},
          {1, std::bind(&IASComputer::subtract, this)},
          {2, std::bind(&IASComputer::store, this)},
          {3, std::bind(&IASComputer::load, this)},
          {4, std::bind(&IASComputer::input, this)},
          {5, std::bind(&IASComputer::output, this)},
          {6, std::bind(&IASComputer::jumpIfPos, this)},
          {7, std::bind(&IASComputer::add, this)},
      }
{
    m_memory[31] = 1;
}

// Handles the fetch and execute cycle
void IASComputer::run()
{
    while (true) {
        std::cout << "\n\n\n ========= Start of Next Cycle =========\n";
        std::cout << "Program counter: " << (int)m_registers.programCounter
                  << "\n";

        if (m_registers.programCounter == (int)m_memory.size()) {
            break;
        }

        fetch(); // FETCH

        printMidCycleState();

        if (getOpcodeFromInstr() == INSTRUCTION_END) {
            break;
        }

        execute(); // EXECUTE... order 66
    }
}

// Fetches the next instruction from memory
void IASComputer::fetch()
{
    m_registers.memoryAddress = m_registers.programCounter++;
    m_registers.memoryBuffer = m_memory[m_registers.memoryAddress];
    m_registers.instruction = m_registers.memoryBuffer;
}

// Executes next instruction
void IASComputer::execute()
{
    Word opcode = getOpcodeFromInstr();
    try {
        m_commandMap.at(opcode)();
    }
    catch (std::out_of_range &e) {
        std::cout << "Opcode: " << (int)opcode << " unknown\n";
    }
}

/*
    Bunch of instructions. These are the opcodes.
*/
void IASComputer::add() // 0
{
    m_registers.accumulator += getValueStoredAtInstrAddress();
}

void IASComputer::subtract()
{
    m_registers.accumulator -= getValueStoredAtInstrAddress();
}

void IASComputer::store()
{
    auto address = getMemAddrFromInstr();
    m_memory.at(address) = m_registers.accumulator;
}

void IASComputer::load()
{
    m_registers.accumulator = getValueStoredAtInstrAddress();
}

// TODO use I/O registers?
void IASComputer::input()
{
    std::cout << "Please input a value: ";
    std::cin >> m_registers.accumulator;
}

// TODO use I/O registers?
void IASComputer::output()
{
    std::cout << "Output: " << (int)m_registers.accumulator << "\n";
}

void IASComputer::jumpIfPos()
{
    if (m_registers.accumulator > 0) {
        auto address = getMemAddrFromInstr();
        m_registers.programCounter = (RegType)address;
    }
}

/*
    END OF INSTRUCTION FUNCTIONS
*/

// Extracts the memory address from the instruction register
Word IASComputer::getMemAddrFromInstr() const
{
    return (Word)m_registers.instruction & 0x1F;
}

// Extracts the opcode address from the instruction register
Word IASComputer::getOpcodeFromInstr() const
{
    return m_registers.instruction >> MEMORY_BITS;
}

// Extracts the memory address from the instruction register
// and gets the value stored there
Word IASComputer::getValueStoredAtInstrAddress() const
{
    return m_memory.at(getMemAddrFromInstr());
}

/*
    Bunch of functions which print some states and that
*/
void IASComputer::printMidCycleState() const
{
    std::cout << "Instruction Fetched. \n";
    printOpcodeAndAddress();
    std::cout << "Description: " << opcodeString.at(getOpcodeFromInstr())
              << "\n";
}

void IASComputer::printOpcodeAndAddress() const
{
    int op = (int)getOpcodeFromInstr();
    int ad = (int)getMemAddrFromInstr();

    std::cout << "Opcode:  " << std::setw(4) << op << " " << std::bitset<8>(op)
              << "\n"
              << "Address: " << std::setw(4) << ad << " " << std::bitset<8>(ad)
              << "\n";
}

void IASComputer::printFullState() const
{
#ifdef PRINT_STATE
    std::cout << "\n"
              << "\nAccumulator Register      " << std::setw(4) << m_accumulator
              << " " << std::bitset<16>(m_accumulator)
              << "\nMemory Buffer  Register:  " << std::setw(4)
              << m_memBufferRegister << " "
              << std::bitset<8>(m_memBufferRegister)
              << "\nMemory Address Register:  " << std::setw(4)
              << m_memAddressRegister << " "
              << std::bitset<8>(m_memAddressRegister)
              << "\nInstruction Register:     " << std::setw(4)
              << m_instructionRegister << " "
              << std::bitset<8>(m_instructionRegister)
              << "\nProgram Counter Register: " << std::setw(4)
              << m_programCounter << " " << std::bitset<8>(m_programCounter)
              << "\n";
#endif // PRINT_STATE
}
