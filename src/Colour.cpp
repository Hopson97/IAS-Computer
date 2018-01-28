#include "Colour.h"

#include <cstdint>

void setTextColour(TextColour colour)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (uint16_t)colour);
}

std::ostream& operator<<(std::ostream& stream, TextColour colour)
{
    setTextColour(colour);
    return stream;
}


