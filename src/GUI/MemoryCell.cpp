#include "IASFrontEnd.h"

MemoryCell::MemoryCell(int memoryLocation, int x, int y, const sf::Font &font)
    : m_memLocation((RegType)memoryLocation)
{
    m_bg.setSize({MemoryCell::XSIZE, MemoryCell::YSIZE});
    m_bg.move(x, y);

    m_bg.setOutlineThickness(2);
    m_bg.setOutlineColor({170, 170, 170});
    m_bg.setFillColor({80, 80, 80});

    m_memLocationDisplay.setCharacterSize(10);
    m_memoryValueDiplay.setCharacterSize(14);

    m_memLocationDisplay.setFont(font);
    m_memoryValueDiplay.setFont(font);

    m_memLocationDisplay.setString(std::to_string(memoryLocation));

    m_memLocationDisplay.move(x + 5, y + 2);
    m_memoryValueDiplay.move(x + 20, y + 10);
}

void MemoryCell::update(Word newValue, RegType activeAddress)
{
    m_memoryValueDiplay.setString(getDecAndBinString(newValue));
    if (newValue != currentValue) {
        currentValue = newValue;
        m_bg.setOutlineColor(sf::Color::Red);
    }
    else if (activeAddress == m_memLocation) {
        m_bg.setOutlineColor(sf::Color::Green);
    }
    else {
        m_bg.setOutlineColor({170, 170, 170});
    }
}

void MemoryCell::draw(sf::RenderWindow &window)
{
    window.draw(m_bg);
    window.draw(m_memLocationDisplay);
    window.draw(m_memoryValueDiplay);
}
