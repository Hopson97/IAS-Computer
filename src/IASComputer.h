#pragma once

#include <array>
#include <functional>
#include <unordered_map>

using Memory  = std::array<uint8_t, 32>;
using RegType = int16_t;

class IASComputer
{
    public:
        IASComputer(const Memory& memory);
        void run();

    private:
        void fetch();
        void execute();

        void add        ();
        void subtract   ();
        void store      ();
        void load       ();
        void input      ();
        void output     ();
        void jumpIfPos  ();

        Memory m_memory;
        std::unordered_map<uint8_t, std::function<void(void)>> m_commandMap;


        //registers
        RegType m_accumulator = 0;
        RegType m_memBufferRegister = 0;
        RegType m_memAddressRegister = 0;
        RegType m_instructionRegister = 0;
        RegType m_programCounter = 0;
        RegType IOAddressRegister = 0;
        RegType IOBufferRegister = 0;
};
