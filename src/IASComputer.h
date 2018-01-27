#pragma once

#include <array>
#include <functional>
#include <unordered_map>

using Word  = uint8_t;
using Memory  = std::array<Word, 64>;
using RegType = int16_t;

constexpr Word OPCODE_BITS   = 3;
constexpr Word MEMORY_BITS   = 5;
constexpr Word END_OF_FILE   = 7;

class IASComputer
{
    public:
        IASComputer(const Memory& memory);
        void run();

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

        Word getMemAddrFromInstr() const;
        Word getOpcodeFromInstr() const;
        Word getValueStoredAtInstrAddress() const;

        void printOpcodeAndAddress();

        void printFullState();

        Memory m_memory;
        std::unordered_map<Word, std::function<void(void)>> m_commandMap;


        //registers
        RegType m_accumulator = 0;
        RegType m_memBufferRegister = 0;
        RegType m_memAddressRegister = 0;
        RegType m_instructionRegister = 0;
        RegType m_programCounter = 0;
        RegType IOAddressRegister = 0;
        RegType IOBufferRegister = 0;
};
