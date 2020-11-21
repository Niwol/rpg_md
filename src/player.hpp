#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dynamic.hpp"

enum inputKeys {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,

    KEY_Z,
    KEY_S,
    KEY_Q,
    KEY_D,

    KEY_SPACE,

    KEY_TOTAL
};

enum stats {
    IDLE,
    WALKING
};

class cPlayer : public cDynamic {
public:
    cPlayer(SDL_Window*, SDL_Renderer*, cMap* map, int currentCellCol, int currentCellRow, std::string name = "Object");

    void handleInput(SDL_Event& e);
    void update();

private:
    bool m_keyHold[KEY_TOTAL];
    int m_currentStat;
};

#endif // PLAYER_HPP