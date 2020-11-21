#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "gameObject.hpp"
#include "map.hpp"
#include "render.hpp"

constexpr int NUMBER_OF_MOVE_STEPS = 25;

class cMap;

enum moveDirection {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
};

class cDynamic : public cGameObject {
public:
    cDynamic(SDL_Window*, SDL_Renderer*, cMap* map, int currentCellCol, int currentCellRow, std::string name = "Object");
    ~cDynamic();

    bool load(std::string path);

    void move(int direction, int animation);

    void update();
    void render();

protected:
    int m_health;

    // For the movement
    float m_offCellX, m_offCellY;
    float m_step;
    int m_numberOfSteps;
    int m_currentFaceDirection;
    int m_previousFaceDirection;

    // In relation to the map:
    cMap* m_map;
    int m_currentCellCol;
    int m_currentCellRow;

    // Rendering
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    cRender m_render;
};

#endif