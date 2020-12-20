#include "dynamic.hpp"

cDynamic::cDynamic(SDL_Window* window, SDL_Renderer* renderer, cMap* map, int currentCellCol, int currentCellRow, std::string name)
    : cGameObject(name)
    , m_health(100)
    , m_offCellX(0)
    , m_offCellY(0)
    , m_step(0)
    , m_numberOfSteps(0)
    , m_currentFaceDirection(MOVE_DOWN)
    , m_previousFaceDirection(MOVE_DOWN)
    , m_map(map)
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
        m_render.startAnimation(ANIMATION_KEY_IDLE_DOWN);

    return success;
}

void cDynamic::move(int direction, int animation)
{
    if (m_numberOfSteps == 0) {
        switch (direction) {
        case MOVE_UP:
            if (m_currentCellRow > 0) {
                m_currentCellRow--;
                m_offCellY = m_map->get_tileHeigth();

                m_numberOfSteps = NUMBER_OF_MOVE_STEPS;
                m_step = m_offCellY / m_numberOfSteps;

                if (m_currentFaceDirection != m_previousFaceDirection) {
                    m_render.startAnimation(animation);
                    m_previousFaceDirection = m_currentFaceDirection;
                }
            }
            break;

        case MOVE_DOWN:
            if (m_currentCellRow < m_map->get_rows() - 1) {
                m_currentCellRow++;
                m_offCellY = -(m_map->get_tileHeigth());

                m_numberOfSteps = NUMBER_OF_MOVE_STEPS;
                m_step = m_offCellY / m_numberOfSteps;

                if (m_currentFaceDirection != m_previousFaceDirection) {
                    m_render.startAnimation(animation);
                    m_previousFaceDirection = m_currentFaceDirection;
                }
            }
            break;

        case MOVE_LEFT:
            if (m_currentCellCol > 0) {
                m_currentCellCol--;
                m_offCellX = m_map->get_tileWidth();

                m_numberOfSteps = NUMBER_OF_MOVE_STEPS;
                m_step = m_offCellX / m_numberOfSteps;

                if (m_currentFaceDirection != m_previousFaceDirection) {
                    m_render.startAnimation(animation);
                    m_previousFaceDirection = m_currentFaceDirection;
                }
            }
            break;

        case MOVE_RIGHT:
            if (m_currentCellCol < m_map->get_cols() - 1) {
                m_currentCellCol++;
                m_offCellX = -(m_map->get_tileWidth());

                m_numberOfSteps = NUMBER_OF_MOVE_STEPS;
                m_step = m_offCellX / m_numberOfSteps;

                if (m_currentFaceDirection != m_previousFaceDirection) {
                    m_render.startAnimation(animation);
                    m_previousFaceDirection = m_currentFaceDirection;
                }
            }
            break;
        }
    } else {

        m_numberOfSteps--;
        if (m_numberOfSteps == 0) {
            m_offCellX = 0;
            m_offCellY = 0;
        } else {
            m_offCellX -= m_offCellX == 0 ? 0 : m_step;
            m_offCellY -= m_offCellY == 0 ? 0 : m_step;
        }
    }
}

void cDynamic::update()
{
    m_render.nextFrame();
}

void cDynamic::render()
{
    int offX, offY;
    int x, y;

    m_map->get_position(&offX, &offY);

    x = m_map->get_tileWidth() * m_currentCellCol + offX + m_offCellX;
    y = m_map->get_tileHeigth() * m_currentCellRow + offY + m_offCellY;

    m_render.render(x, y);
}