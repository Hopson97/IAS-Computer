#ifndef IASFrontEnd_H_INCLUDED
#define IASFrontEnd_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "IASComputer.h"

class IASFrontEnd
{
    public:
        IASFrontEnd(const Memory& memory);

        void run();

    private:
        void tryCloseWindow();

        sf::RenderWindow    m_window;
        sf::Font            m_mainFont;

        IASComputer         m_iasComputer;
};

#endif // IASFrontEnd_H_INCLUDED
