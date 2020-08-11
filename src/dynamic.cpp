#include "dynamic.hpp"

cDynamic::cDynamic(int currentCellCol, int currentCellRow, std::string name)
    : cGameObject(name)
{
    m_health = 100;

    m_currentCellCol = currentCellCol;
    m_currentCellRow = currentCellRow;
}

cDynamic::~cDynamic()
{
}

bool cDynamic::loadSpriteSheet(SDL_Window* window, SDL_Renderer* renderer, std::string path)
{
    return m_spriteSheet.loadFromFile(window, renderer, path, true);
}

void cDynamic::render(SDL_Renderer* renderer, cMap& map)
{
    int offX, offY;
    int tileW, tileH;

    SDL_Rect rect;

    map.get_position(&offX, &offY);
    map.get_tileDymentions(&tileW, &tileH);

    rect = { tileW * m_currentCellCol + offX, tileH * m_currentCellRow + offY, tileW, tileH };

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    rect.x = 0;
    rect.y = 0;

    m_spriteSheet.render(tileW * m_currentCellCol + offX, tileH * m_currentCellRow + offY, &rect);
}