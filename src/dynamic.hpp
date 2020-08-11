#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "gameObject.hpp"
#include "map.hpp"

class cDynamic : public cGameObject {
public:
    cDynamic(int currentCellCol, int currentCellRow, std::string name = "Object");
    ~cDynamic();

    bool loadSpriteSheet(SDL_Window* window, SDL_Renderer* renderer, std::string path);

    // Placeholder function
    void render(SDL_Renderer* renderer, cMap& map);

private:
    int m_health;

    int m_currentCellCol;
    int m_currentCellRow;

    cTexture m_spriteSheet;
};

#endif