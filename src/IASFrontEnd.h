#ifndef IASFrontEnd_H_INCLUDED
#define IASFrontEnd_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "IASComputer.h"


class IASFrontEnd
{
    constexpr static int REG_GUI_X = 20;
    constexpr static int REG_GUI_Y = 160;

    constexpr static int INS_GUI_X = 20;
    constexpr static int INS_GUI_Y = 20;

    constexpr static int MEM_GUI_X = 510;
    constexpr static int MEM_GUI_Y = 185;

    constexpr static int TEXT_HEIGHT = 30;

    class Section
    {
        public:
            void init(const std::string& title, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Font& font);

            void draw(sf::RenderWindow& window);

        private:
            sf::RectangleShape m_background;
            sf::Text m_titleText;
    };

    class NormalCell
    {
        public:
            NormalCell(sf::Font& font, const std::string& title, int valueXOffset);

            void update(Word newValue);
            void update(const std::string& newValue);
            void draw(sf::RenderWindow& window);

            void moveText(int x, int y);

        private:
            sf::Text m_title;
            sf::Text m_valueDisplay;

            int m_currentValue;
    };

    class MemoryCell
    {
        public:
            MemoryCell(int memoryLocation, int x, int y, const sf::Font& font);

            void update (Word newValue);
            void draw   (sf::RenderWindow& window);

            constexpr static int XSIZE = 150;
            constexpr static int YSIZE = 40;


        private:
            sf::RectangleShape m_bg;
            sf::Text m_memLocationDisplay;
            sf::Text m_memoryValueDiplay;

            int currentValue = 0;
    };

    public:
        IASFrontEnd(const Memory& memory);

        void run(bool useGui);

    private:
        void tryCloseWindow();

        void updateDisplays             ();
        void updateRegisterDisplay      ();
        void updateInstructionDisplay   ();
        void updateMemoryDisplay        ();

        void cycleComputer ();
        void render ();

        void initRegisterDisplay();
        void initInstructionDisplay();

        float m_tickDelay = 1.0f;

        sf::RenderWindow    m_window;
        sf::Font            m_mainFont;

        IASComputer m_iasComputer;

        Section m_registerSect;
        Section m_instructionSect;
        Section m_memorySect;

        std::vector<NormalCell> m_registerDisplay;
        std::vector<NormalCell> m_instructionDisplay;

        std::vector<MemoryCell> m_memoryCells;


};

#endif // IASFrontEnd_H_INCLUDED
