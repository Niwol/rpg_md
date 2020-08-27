#include "dynamic.hpp"

cDynamic::cDynamic(
    SDL_Window* window,
    SDL_Renderer* renderer,
    int currentCellCol,
    int currentCellRow,
    std::string name)
    : cGameObject(name)
    , m_health(100)
    , m_currentCellCol(currentCellCol)
    , m_currentCellRow(currentCellRow)
    , m_window(window)
    , m_renderer(renderer)
    , m_render(window, renderer)
{
}

cDynamic::~cDynamic()
{
}

bool cDynamic::load(std::string path)
{
    return m_render.load(path);
}

void cDynamic::render(cMap& map)
{
    int offX, offY;
    int tileW, tileH;

    SDL_Rect rect;

    map.get_position(&offX, &offY);
    map.get_tileDymentions(&tileW, &tileH);

    rect = { tileW * m_currentCellCol + offX, tileH * m_currentCellRow + offY, tileW, tileH };

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(m_renderer, &rect);

    rect.x = 0;
    rect.y = 0;
}