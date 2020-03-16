#ifndef NORMCELL_H
#define NORMCELL_H

#include <SFML/Graphics.hpp>

// Class to represent the display of a title, and a value
// For example, "Opcode: 4 00000100"
class NormalCell {
  public:
    NormalCell(sf::Font &font, const std::string &title, int valueXOffset);

    void update(Word newValue);
    void update(const std::string &newValue);
    void draw(sf::RenderWindow &window);

    void moveText(int x, int y);

  private:
    sf::Text m_title;
    sf::Text m_valueDisplay;

    int m_currentValue;
};

#endif // NORMCELL_H
