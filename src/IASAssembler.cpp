#include "IASAssembler.h"
#include <iostream>
#include <fstream>

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

void IASAssembler::parseLine(const std::string& line) {
}
