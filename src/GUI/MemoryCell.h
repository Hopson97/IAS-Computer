#ifndef MEMCELL_H
#define MEMCELL_H

#include <SFML/Graphics.hpp>

// Class to represent the display of a memory address cell
class MemoryCell {
  public:
    MemoryCell(int memoryLocation, int x, int y, const sf::Font &font);

    void update(Word newValue, RegType activeAddress);
    void draw(sf::RenderWindow &window);

    constexpr static int XSIZE = 160;
    constexpr static int YSIZE = 45;

  private:
    sf::RectangleShape m_bg;
    sf::Text m_memLocationDisplay;
    sf::Text m_memoryValueDiplay;

    int currentValue = 0;
    RegType m_memLocation;
};

#endif // MEMCELL_H
