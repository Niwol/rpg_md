#include "character.hpp"

cCharacter::cCharacter(SDL_Window* window, SDL_Renderer* renderer, int currentCellCol, int currentCellRow, std::string name)
    : cDynamic(window, renderer, currentCellCol, currentCellRow, name)
    , m_x(312)
    , m_y(90)
    , m_speed(2.0f)
    , m_currentState(IDLE)
    , m_currentFrame(0)
    , m_faceDirection(DOWN)
    , m_mainSpriteSheet(window, renderer)
{
    for (int i = 0; i < 5; i++)
        m_keyHeld[i] = false;
}

cCharacter::~cCharacter()
{
    m_mainSpriteSheet.free();
}

bool cCharacter::loadSpriteSheet(std::string path)
{
    return m_mainSpriteSheet.loadFromFile(path, true);
}

void cCharacter::render(cMap& map)
{
    SDL_Rect renderQuad = { 0, 0, m_mainSpriteSheet.get_width() / 4, m_mainSpriteSheet.get_height() / 4 };

    switch (m_faceDirection) {
    case UP:
        renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 3;
        break;
    case DOWN:
        renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 0;
        break;
    case LEFT:
        renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 1;
        break;
    case RIGHT:
        renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 2;
        break;
    }

    if (m_currentState == WALKING) {
        switch (m_currentFrame / 10) {
        case 0:
            renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 0;
            break;
        case 1:
            renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 1;
            break;
        case 2:
            renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 2;
            break;
        case 3:
            renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 3;
            break;
        }
    }

    m_mainSpriteSheet.render(m_x, m_y, &renderQuad);

    // New Rendering

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);

    int x, y;
    int w, h;

    map.get_position(&x, &y);
    w = map.get_tileWidth();
    h = map.get_tileHeigth();

    for (int i = 0; i < (w < h ? w : h) / 2; i++) {
        SDL_Rect rect = { x + m_currentCellCol * w + i, y + m_currentCellRow * h + i, w - i * 2, h - i * 2 };
        SDL_RenderDrawRect(m_renderer, &rect);
    }

    //m_render.render(10, 10);
}

void cCharacter::handleEvent(SDL_Event& e)
{
    switch (e.type) {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_z:
            if (!m_keyHeld[UP]) {
                m_keyHeld[UP] = true;
                m_faceDirection = UP;
            }
            break;

        case SDLK_s:
            if (!m_keyHeld[DOWN]) {
                m_keyHeld[DOWN] = true;
                m_faceDirection = DOWN;
            }
            break;

        case SDLK_q:
            if (!m_keyHeld[LEFT]) {
                m_keyHeld[LEFT] = true;
                m_faceDirection = LEFT;
            }
            break;

        case SDLK_d:
            if (!m_keyHeld[RIGHT]) {
                m_keyHeld[RIGHT] = true;
                m_faceDirection = RIGHT;
            }
            break;
        }

        switch (e.key.keysym.sym) {
        case SDLK_z:
        case SDLK_s:
        case SDLK_q:
        case SDLK_d:
            if (m_currentState != WALKING)
                m_currentFrame = 10;

            m_currentState = WALKING;
        }
        break;

    case SDL_KEYUP:
        switch (e.key.keysym.sym) {
        case SDLK_z:
            m_keyHeld[UP] = false;
            break;
        case SDLK_s:
            m_keyHeld[DOWN] = false;
            break;
        case SDLK_q:
            m_keyHeld[LEFT] = false;
            break;
        case SDLK_d:
            m_keyHeld[RIGHT] = false;
            break;
        }
        break;
    }

    if (m_keyHeld[UP] || m_keyHeld[DOWN] || m_keyHeld[LEFT] || m_keyHeld[RIGHT]) {
        if ((m_faceDirection == UP && !m_keyHeld[UP]) || (m_faceDirection == DOWN && !m_keyHeld[DOWN]) || (m_faceDirection == LEFT && !m_keyHeld[LEFT]) || (m_faceDirection == RIGHT && !m_keyHeld[RIGHT])) {
            int i = 4;
            while (!m_keyHeld[i] && i > 0)
                i--;
            m_faceDirection = i;
        }
    } else
        m_currentState = IDLE;
}

void cCharacter::move()
{
    if (m_currentState == WALKING) {
        switch (m_faceDirection) {
        case UP:
            m_y -= m_speed;
            break;
        case DOWN:
            m_y += m_speed;
            break;
        case LEFT:
            m_x -= m_speed;
            break;
        case RIGHT:
            m_x += m_speed;
            break;
        }
    }
}

void cCharacter::nextFrame()
{
    switch (m_currentState) {
    case IDLE:
        m_currentFrame = 0;
        break;

    case WALKING:
        m_currentFrame++;

        if (m_currentFrame / 10 > 3)
            m_currentFrame = 0;
        break;
    }
}
