#include "IASAssembler.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <bitset>

namespace
{
    const std::unordered_map<std::string, uint8_t> strToOpcode
    {
        {"add", 0},
        {"sub", 1},
        {"sta", 2},
        {"lda", 3},
        {"inp", 4},
        {"out", 5},
        {"jip", 6},
    };

    auto split(const std::string& str)
    {
        std::istringstream stream(str);
        std::vector<std::string> tokens{
            std::istream_iterator<std::string>(stream),
            std::istream_iterator<std::string>()
        };
        return tokens;
    }

    void toLowerCase(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

}

IASAssembler::IASAssembler()
{
    m_assembledCode.fill(0);
}

Memory IASAssembler::assembleFile(const char* fileName)
{
    std::ifstream inFile(fileName);

    if (inFile.good()) {
        parse(inFile);
    } else {
        std::cout << "File " << fileName << " does not exist.";
    }
    return m_assembledCode;
}


void IASAssembler::parse(std::ifstream& inFile)
{
    std::string line;
    while (std::getline(inFile, line)) {
        parseLine(line);
    }
}

void IASAssembler::parseLine(const std::string& line)
{
    auto tokens = split(line);
    toLowerCase(tokens[0]);
    auto opcode = strToOpcode.at(tokens.at(0));

    uint8_t instruction = opcode << MEMORY_BITS;
    if (tokens.size() == 2) {
        uint8_t address = (uint8_t)std::stoi(tokens[1]);
        instruction |= address;
    }
    m_assembledCode[m_instructionCount++] = instruction;
}












