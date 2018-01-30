#include "IASFrontEnd.h"

IASFrontEnd::IASFrontEnd(const Memory& memory)
:   m_window        ({1280, 720}, "8-bit IAS Computer")
,   m_iasComputer   (memory)
{

}

void IASFrontEnd::run()
{
    /*
    while (m_window.isOpen()) {

        m_window.clear();

        m_window.display();
        tryCloseWindow();
    }
    */
    m_window.close();
    m_iasComputer.run();
}


//Check if user has closed window
void IASFrontEnd::tryCloseWindow()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}


