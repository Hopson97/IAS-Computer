#ifndef IASCOMPUTER_H
#define IASCOMPUTER_H

#include <array>
#include <functional>
#include <unordered_map>

using Word      = uint8_t;
using Memory    = std::array<Word, 32>;
using RegType   = int16_t;

constexpr Word OPCODE_BITS      = 3;
constexpr Word MEMORY_BITS      = 5;
constexpr Word INSTRUCTION_END  = 7;
constexpr int  NUM_REGISTERS    = 7;

const std::unordered_map<Word, std::string> opcodeString {
    {0, "Add number at memory address to the accumulator." },
    {1, "Subtract the number the at memory address from the accumulator." },
    {2, "Store the number in the accumulator to the memory address." },
    {3, "Load number from the memory address to the accumulator." },
    {4, "Get user input, place result in the accumulator." },
    {5, "Output the number stored in the accumulator." },
    {6, "Set program counter to the memory address, given the accumulator's value is positive"},
    {7, "Exit the program."},
};


class IASComputer
{
    //registers
    struct Registers {
        RegType accumulator         = 0;
        RegType memoryBuffer        = 0;
        RegType memoryAddress       = 0;
        RegType instruction         = 0;
        RegType programCounter      = 0;
        RegType IOAddressRegister   = 0;
        RegType IOBufferRegister    = 0;
    };

    public:
        IASComputer(const Memory& memory);
        void run();

        const Memory& getMemory             () const { return m_memory; }
        const RegType* getFirstRegister     () const { return &m_registers.accumulator; }
        RegType getProgramCounter           () const { return m_registers.programCounter; }

        Word getMemAddrFromInstr            () const;
        Word getOpcodeFromInstr             () const;
        Word getValueStoredAtInstrAddress   () const;

        void fetch();
        void execute();

    private:
        //IAS Custom Instruction Set
        void add        ();
        void subtract   ();
        void store      ();
        void load       ();
        void input      ();
        void output     ();
        void jumpIfPos  ();

        void printMidCycleState     () const;
        void printOpcodeAndAddress  () const;
        void printFullState         () const;

        Memory      m_memory;
        Registers   m_registers;

        const std::unordered_map<Word, std::function<void(void)>> m_commandMap;
};

#endif // IASCOMPUTER_H
