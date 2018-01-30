#ifndef IASFrontEnd_H_INCLUDED
#define IASFrontEnd_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "IASComputer.h"


class IASFrontEnd
{
    public:
        IASFrontEnd(const Memory& memory);

        void run(bool useGui);

    private:
        void tryCloseWindow();
        void updateRegisterDisplay();

        void initRegisterDisplay();

        sf::RenderWindow    m_window;
        sf::Font            m_mainFont;

        IASComputer m_iasComputer;

        std::vector<sf::Text> m_registerDisplay;
        std::vector<sf::Text> m_registerValueDisplay;


};

#endif // IASFrontEnd_H_INCLUDED
