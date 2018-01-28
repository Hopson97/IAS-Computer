#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

#define MIN
#include <windows.h>
#include <ostream>

enum class TextColour
{
    Black             = 0,
    DarkBlue          = FOREGROUND_BLUE,
    DarkGreen         = FOREGROUND_GREEN,
    DarkCyan          = FOREGROUND_GREEN    | FOREGROUND_BLUE,
    DarkRed           = FOREGROUND_RED,
    DarkMagenta       = FOREGROUND_RED      | FOREGROUND_BLUE,
    DarkYellow        = FOREGROUND_RED      | FOREGROUND_GREEN,
    DarkGrey          = FOREGROUND_RED      | FOREGROUND_GREEN | FOREGROUND_BLUE,
    Grey              = FOREGROUND_INTENSITY,
    Blue              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    Green             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    Cyan              = FOREGROUND_INTENSITY | FOREGROUND_GREEN     | FOREGROUND_BLUE,
    Red               = FOREGROUND_INTENSITY | FOREGROUND_RED,
    Magenta           = FOREGROUND_INTENSITY | FOREGROUND_RED       | FOREGROUND_BLUE,
    Yellow            = FOREGROUND_INTENSITY | FOREGROUND_RED       | FOREGROUND_GREEN,
    White             = FOREGROUND_INTENSITY | FOREGROUND_RED       | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

void setTextColour(TextColour colour);

std::ostream& operator << (std::ostream& stream, TextColour colour);

#endif // COLOUR_H_INCLUDED
