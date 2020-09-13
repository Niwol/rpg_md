#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>

#include "texture.hpp"

struct sCell {
    bool solid;

    int tmCol;
    int tmRow;
};

class cMap {
public:
    /**
     * @brief Construct a new c Map object
     * 
     * @param cols number of collums of the map
     * @param rows number of rows of the map
     */
    cMap(SDL_Window*, SDL_Renderer*, int cols, int rows);

    /**
     * @brief Destroy the c Map object
     * 
     */
    ~cMap();

    /**
     * @brief Loads the tilemap texture for the map
     * 
     * @param window The window in which the tilemap texture renders its tiles
     * @param renderer The renderer which renders the tiles
     * @param path The path to the tilemap texture
     * @param cols Number of tiles in collums of the tilemap texture
     * @param rows Number of tiles in rows of the tilemap texture
     * @param alpha Flag to set to true if there is alpha in the texture
     * @return true in succes
     * @return false in faliure
     */
    bool loadTileMap(std::string path, int cols, int rows, bool alpha);

    /**
     * @brief Loads a map by reading a file
     * 
     * @param path The path to the file
     * @return true in succes
     * @return false in faliure
     */
    bool load(std::string path);

    /**
     * @brief Saves the map to a file
     * 
     * @param path The path to the save file
     * @return true in succes
     * @return false in faliure
     */
    bool save(std::string path);

    /**
     * @brief Renders the map to the screen. Needs to have a tilemap texture loaded
     * 
     * @param renderer The renderer which renders the border map
     * @param x The x coordonate to render the map to
     * @param y The y coordonate to render the map to
     */
    void render(int x = 0, int y = 0);

    /**
     * @brief Renders the hole tilemap texture to the screen. Useful for creating maps and debugging
     * 
     * @param renderer The renderer which renders the selected tile border on the tilemap
     * @param x The x coordonate to render the tilemap texture to
     * @param y The y coordonate to render the tilemap texture to
     */
    void renderTilemap(int x, int y);

    /**
     * @brief Handels the events related to create a map: tile selection and placing
     * 
     * @param e The event to handle
     */
    void handleEvent(SDL_Event& e);

    // Accessors
    /**
     * @brief Get the position of the map
     * 
     * @param x gets the x position
     * @param y gets the y position
     */
    void get_position(int* x, int* y);

    /**
     * @brief Get the tile width
     * 
     * @return int
     */
    int get_tileWidth();

    /**
     * @brief Get the tile heigth
     * 
     * @return int
     */
    int get_tileHeigth();

    /**
     * @brief Get the number of collums of the map
     * 
     * @return int
     */
    int get_cols();

    /**
     * @brief Get the number of rows of the map
     * 
     * @return int 
     */
    int get_rows();

private:
    cTexture m_tilemapTexture;

    int m_tileWidth;
    int m_tileHeight;

    int m_tilemapCols;
    int m_tilemapRows;

    int m_cols;
    int m_rows;

    int m_nCells;
    sCell* m_cells;

    int m_selectedTile;

    int m_mouseX;
    int m_mouseY;
    bool m_mouseButton1Hold;

    // Map rendering position
    int m_posX;
    int m_posY;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif