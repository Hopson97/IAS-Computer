#include "IASApp.h"

IASApp::IASApp(const Memory& memory)
:   m_window        ({1280, 720}, "8-bit IAS Computer")
,   m_iasComputer   (memory)
{

}

void IASApp::run()
{
    while (m_window.isOpen()) {

        m_window.clear();

        m_window.display();
        tryCloseWindow();
    }
    m_iasComputer.run();
}


//Check if user has closed window
void IASApp::tryCloseWindow()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}


