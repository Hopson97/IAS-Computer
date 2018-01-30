#ifndef IASFrontEnd_H_INCLUDED
#define IASFrontEnd_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "IASComputer.h"


class IASFrontEnd
{
    class Section
    {
        public:
            void init(const std::string& title, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

            void draw(sf::RenderWindow& window);

        private:
            sf::RectangleShape m_background;
            sf::Text m_titleText;
    };

    public:
        IASFrontEnd(const Memory& memory);

        void run(bool useGui);

    private:
        void tryCloseWindow();
        void updateRegisterDisplay();
        void cycleComputer();
        void render();

        void initRegisterDisplay();

        sf::RenderWindow    m_window;
        sf::Font            m_mainFont;

        IASComputer m_iasComputer;

        Section m_registerSect;

        std::vector<sf::Text> m_registerDisplay;
        std::vector<sf::Text> m_registerValueDisplay;


};

#endif // IASFrontEnd_H_INCLUDED
