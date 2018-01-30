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

class IASComputer
{
    public:
        IASComputer(const Memory& memory);
        void run();

        const Memory& getMemory     () const { return m_memory; }

        RegType getAccummulator     () const { return m_accumulator; }
        RegType getMemBufferReg     () const { return m_memBufferRegister; }
        RegType getMemAddressReg    () const { return m_memAddressRegister; }
        RegType getInstructionReg   () const { return m_instructionRegister; }
        RegType getProgramCounter   () const { return m_programCounter; }

    private:
        void fetch();
        void execute();

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

        Memory m_memory;
        const std::unordered_map<Word, std::function<void(void)>> m_commandMap;

        //registers
        RegType m_accumulator           = 0;
        RegType m_memBufferRegister     = 0;
        RegType m_memAddressRegister    = 0;
        RegType m_instructionRegister   = 0;
        RegType m_programCounter        = 0;
        RegType IOAddressRegister       = 0;
        RegType IOBufferRegister        = 0;
};

#endif // IASCOMPUTER_H
