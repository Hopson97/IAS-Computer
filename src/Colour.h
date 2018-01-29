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
    DarkRed           = FOREGROUND_RED,
    Grey              = FOREGROUND_INTENSITY,
    DarkCyan          = FOREGROUND_GREEN        | FOREGROUND_BLUE,
    DarkMagenta       = FOREGROUND_RED          | FOREGROUND_BLUE,
    DarkYellow        = FOREGROUND_RED          | FOREGROUND_GREEN,
    DarkGrey          = FOREGROUND_RED          | FOREGROUND_GREEN  | FOREGROUND_BLUE,
    Blue              = FOREGROUND_INTENSITY    | FOREGROUND_BLUE,
    Green             = FOREGROUND_INTENSITY    | FOREGROUND_GREEN,
    Cyan              = FOREGROUND_INTENSITY    | FOREGROUND_GREEN  | FOREGROUND_BLUE,
    Red               = FOREGROUND_INTENSITY    | FOREGROUND_RED,
    Magenta           = FOREGROUND_INTENSITY    | FOREGROUND_RED    | FOREGROUND_BLUE,
    Yellow            = FOREGROUND_INTENSITY    | FOREGROUND_RED    | FOREGROUND_GREEN,
    White             = FOREGROUND_INTENSITY    | FOREGROUND_RED    | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

const TextColour DefaultCol = TextColour::DarkGrey;

void setTextColour(TextColour colour);

std::ostream& operator << (std::ostream& stream, TextColour colour);

#endif // COLOUR_H_INCLUDED
