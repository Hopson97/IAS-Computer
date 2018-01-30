#ifndef IASAPP_H_INCLUDED
#define IASAPP_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "IASComputer.h"

class IASApp
{
    public:
        IASApp(const Memory& memory);

        void run();

    private:
        void tryCloseWindow();

        sf::RenderWindow    m_window;
        sf::Font            m_mainFont;

        IASComputer         m_iasComputer;
};

#endif // IASAPP_H_INCLUDED
