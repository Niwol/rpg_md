#include "map.hpp"

cMap::cMap(SDL_Window* window, SDL_Renderer* renderer, int cols, int rows)
    : m_tileWidth(0)
    , m_tileHeight(0)
    , m_tilemapCols(0)
    , m_tilemapRows(0)
    , m_cols(cols)
    , m_rows(rows)
    , m_nCells(m_cols * m_rows)
    , m_cells(new sCell[m_nCells])
    , m_selectedTile(0)
    , m_window(window)
    , m_renderer(renderer)
    , m_tilemapTexture(window, renderer)
    , m_mouseButton1Hold(false)
    , m_posX(0)
    , m_posY(0)
{
    for (int i = 0; i < m_nCells; i++) {
        m_cells[i].solid = false;
        m_cells[i].tmCol = 0;
        m_cells[i].tmRow = 0;
    }
}

cMap::~cMap()
{
    m_tilemapTexture.free();
    delete m_cells;
}

bool cMap::loadTileMap(std::string path, int cols, int rows, bool alpha)
{
    if (!m_tilemapTexture.loadFromFile(path, alpha)) {
        printf("Failed to load tilemap texture!\n");
        return false;
    }

    m_tilemapCols = cols;
    m_tilemapRows = rows;

    m_tileWidth = m_tilemapTexture.get_width() / m_tilemapCols;
    m_tileHeight = m_tilemapTexture.get_height() / m_tilemapRows;

    return true;
}

bool cMap::load(std::string path)
{
    std::ifstream file;
    file.open(path);
    if (file.is_open()) {
        for (int i = 0; i < m_nCells; i++) {
            file >> m_cells[i].tmCol >> m_cells[i].tmRow;
        }

        file.close();
        return true;
    } else {
        printf("Could not open file %s\n", path.c_str());

        return false;
    }
}

bool cMap::save(std::string path)
{
    std::ofstream file;
    file.open(path, std::ios::trunc);
    if (file.is_open()) {
        for (int i = 0; i < m_nCells; i++) {
            file << m_cells[i].tmCol << " " << m_cells[i].tmRow << "  ";

            if ((i + 1) % m_cols == 0)
                file << "\n";
        }

        file.close();
        return true;
    } else {
        printf("Could not open file %s\n", path.c_str());

        return false;
    }
}

void cMap::render(int x, int y)
{
    SDL_Color c;
    SDL_GetRenderDrawColor(m_renderer, &c.r, &c.g, &c.b, &c.a);

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_Rect rect = { x - 1, y - 1, m_tileWidth * m_cols + 2, m_tileHeight * m_rows + 2 };
    SDL_RenderDrawRect(m_renderer, &rect);

    SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 255);
    for (int i = 0; i < m_tileHeight * m_rows; i++) {
        int x1 = x;
        int y1 = y + i;

        int x2 = x1 + m_tileWidth * m_cols - 1;
        int y2 = y1;

        SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
    }

    for (int i = 0; i < m_nCells; i++) {
        SDL_Rect clip = { m_cells[i].tmCol * m_tileWidth,
            m_cells[i].tmRow * m_tileHeight,
            m_tileWidth, m_tileHeight };

        m_tilemapTexture.render(x + (i * m_tileWidth) % (m_cols * m_tileWidth),
            y + (i / m_cols) * m_tileHeight,
            &clip);
    }

    SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, c.a);
    m_posX = x;
    m_posY = y;
}

void cMap::renderTilemap(int x, int y)
{
    m_tilemapTexture.render(x, y);

    SDL_Rect rect = { x + (m_selectedTile * m_tileWidth) % m_tilemapTexture.get_width() - 1,
        y + (m_selectedTile / m_tilemapCols) * m_tileHeight - 1,
        m_tileWidth + 2,
        m_tileHeight + 2 };

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(m_renderer, &rect);
}

void cMap::handleEvent(SDL_Event& e)
{
    switch (e.type) {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            if (m_selectedTile >= m_tilemapCols)
                m_selectedTile -= m_tilemapCols;
            else
                m_selectedTile += m_tilemapCols * (m_tilemapRows - 1);
            break;

        case SDLK_DOWN:
            if (m_selectedTile <= m_tilemapCols * (m_tilemapRows - 1) - 1)
                m_selectedTile += m_tilemapCols;
            else
                m_selectedTile -= m_tilemapCols * (m_tilemapRows - 1);
            break;

        case SDLK_LEFT:
            if (m_selectedTile == 0)
                m_selectedTile = m_tilemapCols * m_tilemapRows - 1;
            else
                m_selectedTile--;
            break;

        case SDLK_RIGHT:
            if (m_selectedTile >= m_tilemapCols * m_tilemapRows - 1)
                m_selectedTile = 0;
            else
                m_selectedTile++;
            break;
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (e.button.x > m_posX && e.button.x < m_cols * m_tileWidth + m_posX && e.button.y > m_posY && e.button.y < m_rows * m_tileHeight + m_posY && e.button.button == 1)
            m_mouseButton1Hold = true;

        break;

    case SDL_MOUSEBUTTONUP:
        if (e.button.button == 1)
            m_mouseButton1Hold = false;
        break;
    }

    if (e.button.x > m_posX && e.button.x < m_cols * m_tileWidth + m_posX && e.button.y > m_posY && e.button.y < m_rows * m_tileHeight + m_posY && m_mouseButton1Hold) {
        int x = (e.button.x - m_posX) / m_tileWidth;
        int y = (e.button.y - m_posY) / m_tileHeight;

        m_cells[y * m_cols + x].tmCol = m_selectedTile % m_tilemapCols;
        m_cells[y * m_cols + x].tmRow = m_selectedTile / m_tilemapCols;
    }
}

void cMap::get_position(int* x, int* y)
{
    *x = m_posX;
    *y = m_posY;
}

void cMap::get_tileDymentions(int* w, int* h)
{
    *w = m_tileWidth;
    *h = m_tileHeight;
}