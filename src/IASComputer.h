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

        const Memory& getMemory () const { return m_memory; }

        //Registers getRegisters  () const { return m_registers;}

        const RegType* getFirstRegister() const { return &m_registers.accumulator; }

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

        Word getMemAddrFromInstr            () const;
        Word getOpcodeFromInstr             () const;
        Word getValueStoredAtInstrAddress   () const;

        void printMidCycleState     () const;
        void printOpcodeAndAddress  () const;
        void printFullState         () const;

        Memory      m_memory;
        Registers   m_registers;

        const std::unordered_map<Word, std::function<void(void)>> m_commandMap;
};

#endif // IASCOMPUTER_H
