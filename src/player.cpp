#include "player.hpp"

cPlayer::cPlayer(SDL_Window* window, SDL_Renderer* renderer, cMap* map, int currentCellCol, int currentCellRow, std::string name)
    : cDynamic(window, renderer, map, currentCellCol, currentCellRow, name)
    , m_currentStat(IDLE)
{
    for (int i = 0; i < KEY_TOTAL; i++)
        m_keyHold[i] = false;
}

void cPlayer::handleInput(SDL_Event& e)
{
    switch (e.type) {
    case SDL_KEYDOWN:

        switch (e.key.keysym.sym) {

        case SDLK_z:
            if (m_keyHold[KEY_Z] == false) {
                m_keyHold[KEY_Z] = true;

                m_currentStat = WALKING;
                m_currentFaceDirection = MOVE_UP;
            }
            break;

        case SDLK_s:
            if (m_keyHold[KEY_S] == false) {
                m_keyHold[KEY_S] = true;

                m_currentStat = WALKING;
                m_currentFaceDirection = MOVE_DOWN;
            }
            break;

        case SDLK_q:
            if (m_keyHold[KEY_Q] == false) {
                m_keyHold[KEY_Q] = true;

                m_currentStat = WALKING;
                m_currentFaceDirection = MOVE_LEFT;
            }
            break;

        case SDLK_d:
            if (m_keyHold[KEY_D] == false) {
                m_keyHold[KEY_D] = true;

                m_currentStat = WALKING;
                m_currentFaceDirection = MOVE_RIGHT;
            }
            break;

        default:
            break;
        }

        break;

    case SDL_KEYUP:

        switch (e.key.keysym.sym) {
        case SDLK_z:
            m_keyHold[KEY_Z] = false;
            break;
        case SDLK_s:
            m_keyHold[KEY_S] = false;
            break;
        case SDLK_q:
            m_keyHold[KEY_Q] = false;
            break;
        case SDLK_d:
            m_keyHold[KEY_D] = false;
            break;

        default:
            break;
        }

        if (m_keyHold[KEY_Z] || m_keyHold[KEY_S] || m_keyHold[KEY_Q] || m_keyHold[KEY_D]) {

            if ((m_currentFaceDirection == MOVE_UP && !m_keyHold[KEY_Z])
                || (m_currentFaceDirection == MOVE_DOWN && !m_keyHold[KEY_S])
                || (m_currentFaceDirection == MOVE_LEFT && !m_keyHold[KEY_Q])
                || (m_currentFaceDirection == MOVE_RIGHT && !m_keyHold[KEY_D])) {

                int i = KEY_Z;
                while (!m_keyHold[i] && i < KEY_D)
                    i++;

                m_currentFaceDirection = i - KEY_Z;
            }
        } else
            m_currentStat = IDLE;

        /*
        int i = KEY_Z;
        while (!m_keyHold[i] && i <= KEY_D) {
            i++;
        }

        if (i == KEY_D + 1) {
            m_currentStat = IDLE;
        }*/

        break;
    }
}

void cPlayer::update()
{
    m_render.nextFrame();

    if (m_currentStat == WALKING || m_numberOfSteps != 0) {
        switch (m_currentFaceDirection) {
        case MOVE_UP:
            move(m_currentFaceDirection, ANIMATION_KEY_MOVE_UP);
            break;
        case MOVE_DOWN:
            move(m_currentFaceDirection, ANIMATION_KEY_MOVE_DOWN);
            break;
        case MOVE_LEFT:
            move(m_currentFaceDirection, ANIMATION_KEY_MOVE_LEFT);
            break;
        case MOVE_RIGHT:
            move(m_currentFaceDirection, ANIMATION_KEY_MOVE_RIGHT);
            break;
        }
    }

    if (m_currentStat == IDLE && m_numberOfSteps == 0) {

        switch (m_currentFaceDirection) {
        case MOVE_UP:
            m_render.startAnimation(ANIMATION_KEY_IDLE_UP);
            break;
        case MOVE_DOWN:
            m_render.startAnimation(ANIMATION_KEY_IDLE_DOWN);
            break;
        case MOVE_LEFT:
            m_render.startAnimation(ANIMATION_KEY_IDLE_LEFT);
            break;
        case MOVE_RIGHT:
            m_render.startAnimation(ANIMATION_KEY_IDLE_RIGHT);
            break;
        }

        m_previousFaceDirection = -1;
    }
}
