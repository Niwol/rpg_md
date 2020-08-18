#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "gameObject.hpp"
#include "map.hpp"
#include "render.hpp"

class cDynamic : public cGameObject {
public:
    cDynamic(SDL_Window*, SDL_Renderer*, int currentCellCol, int currentCellRow, int numberOfAnimations, std::string name = "Object");
    ~cDynamic();

    bool loadSpriteSheet(std::string path);

    // Placeholder function
    void render(cMap& map);

protected:
    int m_health;

    int m_currentCellCol;
    int m_currentCellRow;

    SDL_Window* m_window;
    cRender m_render;
    SDL_Renderer* m_renderer;

    cTexture m_spriteSheet;
};

#endif