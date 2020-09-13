#include "dynamic.hpp"

cDynamic::cDynamic(
    SDL_Window* window,
    SDL_Renderer* renderer,
    int currentCellCol,
    int currentCellRow,
    std::string name)
    : cGameObject(name)
    , m_health(100)
    , m_offCellX(0)
    , m_offCellY(0)
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
    bool success = m_render.load(path);

    if (success)
        m_render.startAnimation(4);

    return success;
}

void cDynamic::move(int direction, cMap& map)
{
    if (m_offCellX == 0 && m_offCellY == 0) {
        switch (direction) {
        case MOVE_UP:
            if (m_currentCellRow > 0) {
                m_currentCellRow--;
                m_offCellY = map.get_tileHeigth();

                m_render.startAnimation(MOVE_UP);
            }
            break;

        case MOVE_DOWN:
            if (m_currentCellRow < map.get_rows() - 1) {
                m_currentCellRow++;
                m_offCellY = -(map.get_tileHeigth());

                m_render.startAnimation(MOVE_DOWN);
            }
            break;

        case MOVE_LEFT:
            if (m_currentCellCol > 0) {
                m_currentCellCol--;
                m_offCellX = map.get_tileWidth();

                m_render.startAnimation(MOVE_LEFT);
            }
            break;

        case MOVE_RIGHT:
            if (m_currentCellCol < map.get_cols() - 1) {
                m_currentCellCol++;
                m_offCellX = -(map.get_tileWidth());

                m_render.startAnimation(MOVE_RIGHT);
            }
            break;
        }
    }
}

void cDynamic::update()
{
    m_render.nextFrame();

    if (m_offCellX != 0)
        m_offCellX += m_offCellX < 0 ? 1 : -1;

    if (m_offCellY != 0)
        m_offCellY += m_offCellY < 0 ? 1 : -1;

    if (m_offCellX == 0 && m_offCellY == 0) {
        m_render.restartAnimation();
        m_render.pauseAnimation(true);
    }
}

void cDynamic::render(cMap& map)
{
    int offX, offY;
    int x, y;

    map.get_position(&offX, &offY);

    x = map.get_tileWidth() * m_currentCellCol + offX + m_offCellX;
    y = map.get_tileHeigth() * m_currentCellRow + offY + m_offCellY;

    m_render.render(x, y);
}