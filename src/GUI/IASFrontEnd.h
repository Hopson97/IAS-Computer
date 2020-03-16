#ifndef IASFrontEnd_H_INCLUDED
#define IASFrontEnd_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "../IASComputer.h"

#include "MemoryCell.h"
#include "NormalCell.h"
#include "Section.h"

std::string getDecAndBinString(Word value);

class IASFrontEnd {
    constexpr static int REG_GUI_X = 20;
    constexpr static int REG_GUI_Y = 160;

    constexpr static int INS_GUI_X = REG_GUI_X;
    constexpr static int INS_GUI_Y = 20;

    constexpr static int MEM_GUI_X = 510;
    constexpr static int MEM_GUI_Y = 185;

    constexpr static int IO_GUI_X = REG_GUI_X;
    constexpr static int IO_GUI_Y = 400;

    constexpr static int TEXT_HEIGHT = 30;

  public:
    IASFrontEnd(const Memory &memory);

    void run(bool useGui);

  private:
    void tryCloseWindow();

    void updateDisplays();
    void updateRegisterDisplay();
    void updateInstructionDisplay();
    void updateMemoryDisplay();

    void cycleComputer();
    void render();

    void initRegisterDisplay();
    void initInstructionDisplay();

    float m_tickDelay = 1.0f;

    sf::RenderWindow m_window;
    sf::Font m_mainFont;

    IASComputer m_iasComputer;

    Section m_registerSect;
    Section m_instructionSect;
    Section m_memorySect;
    Section m_sectionIO;

    std::vector<NormalCell> m_registerDisplay;
    std::vector<NormalCell> m_instructionDisplay;

    std::vector<MemoryCell> m_memoryCells;

    bool m_doNextStep = false;
};

#endif // IASFrontEnd_H_INCLUDED
