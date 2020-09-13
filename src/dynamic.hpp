#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "gameObject.hpp"
#include "map.hpp"
#include "render.hpp"

enum moveDirection {
    MOVE_UP = 3,
    MOVE_DOWN = 0,
    MOVE_LEFT = 1,
    MOVE_RIGHT = 2
};

enum dynamicStats {
    IDLE = 4,
    MOVING = 5
};

class cDynamic : public cGameObject {
public:
    cDynamic(SDL_Window*, SDL_Renderer*, int currentCellCol, int currentCellRow, std::string name = "Object");
    ~cDynamic();

    bool load(std::string path);

    void move(int direction, cMap& map);

    void update();
    void render(cMap& map);

protected:
    int m_health;

    float m_offCellX, m_offCellY;

    int m_currentCellCol;
    int m_currentCellRow;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    cRender m_render;
};

#endif