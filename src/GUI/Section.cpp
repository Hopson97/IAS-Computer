#include "IASFrontEnd.h"

void Section::init(const std::string& title,  const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font)
{
    m_titleText.setOutlineThickness(2);
    m_titleText.setFillColor({0, 200, 200});
    m_titleText.setCharacterSize(17);

    m_background.setSize(size);
    m_background.setPosition(position);

    m_background.setOutlineThickness(2);
    m_background.setOutlineColor({150, 150, 150});
    m_background.setFillColor({100, 100, 100});

    m_titleText.setFont     (font);
    m_titleText.move        ({position.x + 5, position.y});
    m_titleText.setString   (title);
}

void Section::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_titleText);

}
