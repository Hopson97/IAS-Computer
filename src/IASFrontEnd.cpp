#include "IASFrontEnd.h"

#include <sstream>
#include <iomanip>
#include <bitset>

IASFrontEnd::IASFrontEnd(const Memory& memory)
:   m_window        ({1280, 720}, "8-bit IAS Computer")
,   m_iasComputer   (memory)
{
    m_window.setFramerateLimit(30);
    m_mainFont.loadFromFile("res/Anonymous.ttf");

    initRegisterDisplay();
}

void IASFrontEnd::run(bool useGui)
{
    if (useGui) {
        sf::Clock c;
        while (m_window.isOpen()) {

            m_window.clear();

            if (c.getElapsedTime() > sf::seconds(0.75)) {
                m_iasComputer.fetch();
                updateRegisterDisplay();
                m_iasComputer.execute();
                c.restart();
            }

            for (int i = 0; i < NUM_REGISTERS; i++) {
                m_window.draw(m_registerDisplay[i]);
                m_window.draw(m_registerValueDisplay[i]);
            }


            m_window.display();
            tryCloseWindow();
        }
    }
    else {
        m_window.close();
        m_iasComputer.run();
    }
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

void IASFrontEnd::updateRegisterDisplay()
{
    auto* start = m_iasComputer.getFirstRegister();
    for (int i = 0; i < NUM_REGISTERS; i++) {
        std::ostringstream stream;
        Word value = *(start + i);
        stream << std::setw(4) << (int)value << " " << std::bitset<8>(value);
        m_registerValueDisplay[i].setString(stream.str());
    }
}

void IASFrontEnd::initRegisterDisplay()
{
    int charSize = 15;
    sf::Font& f = m_mainFont;

    m_registerDisplay.emplace_back("   Accumulator Register: ", f);
    m_registerDisplay.emplace_back(" Memory Buffer Register: ", f);
    m_registerDisplay.emplace_back("Memory Address Register: ", f);
    m_registerDisplay.emplace_back("   Instruction Register: ", f);
    m_registerDisplay.emplace_back("        Program Counter: ", f);
    m_registerDisplay.emplace_back("    IO Address Register: ", f);
    m_registerDisplay.emplace_back("     IO Buffer Register: ", f);

    for (int i = 0; i < NUM_REGISTERS; i++) {
        m_registerValueDisplay.emplace_back("Not Used Yet", f);
    }

    sf::Text temp("ABCDEFGHIJKLMNOPQRSTUVWXYZ", f);
    auto textHeight = temp.getLocalBounds().height;
    temp.setCharacterSize(charSize);

    for (int y = 0; y < NUM_REGISTERS; y++) {
        m_registerDisplay[y].setCharacterSize(charSize);
        m_registerDisplay[y].move(20, 20 + y * textHeight);

        m_registerValueDisplay[y].setCharacterSize(charSize);
        m_registerValueDisplay[y].move(280, 20 + y * textHeight);
    }
}


