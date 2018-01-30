#include "IASFrontEnd.h"

IASFrontEnd::NormalCell::NormalCell(sf::Font& font, const std::string& title, int valueXOffset)
{
    m_title.setString(title);
    m_title.setFont(font);
    m_valueDisplay.setFont(font);

    m_title.setCharacterSize(15);
    m_valueDisplay.setCharacterSize(15);

    m_valueDisplay.move(valueXOffset, 0);
}

void IASFrontEnd::NormalCell::update(Word newValue)
{
    m_valueDisplay.setString(getDecAndBinString(newValue));
    if (newValue != m_currentValue) {
        m_currentValue = newValue;
        m_valueDisplay.setFillColor(sf::Color::Red);
    }
    else {
        m_valueDisplay.setFillColor(sf::Color::White);
    }
}

void IASFrontEnd::NormalCell::update(const std::string& newValue)
{
    m_valueDisplay.setString(newValue);
}


void IASFrontEnd::NormalCell::draw(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_valueDisplay);
}

void IASFrontEnd::NormalCell::moveText(int x, int y)
{
    m_title         .move(x, y);
    m_valueDisplay  .move(x, y);
}
