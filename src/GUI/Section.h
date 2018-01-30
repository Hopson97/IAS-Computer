#ifndef SECT_H
#define SECT_H

#include <SFML/Graphics.hpp>

//Background and title of GUI section
class Section
{
    public:
        void init(const std::string& title, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

        void draw(sf::RenderWindow& window);

    private:
        sf::RectangleShape m_background;
        sf::Text m_titleText;
};

#endif // SECT_H
