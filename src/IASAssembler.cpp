#include "IASAssembler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

namespace
{
    const std::unordered_map<std::string, int> strToOpcode
    {
        {"add", 0},
        {"sub", 1},
        {"str", 2},
        {"lod", 3},
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
    for (auto& token : tokens) {
        std::cout << token << " ... ";
    }
    std::cout << "\n";
}

