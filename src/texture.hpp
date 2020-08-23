#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cTexture {
public:
    // Constructor / destructor
    /**
     * @brief Construct a new c Texture object
     * 
     */
    cTexture(SDL_Window*, SDL_Renderer*);

    /**
     * @brief Destroy the c Texture object
     * 
     */
    ~cTexture();

    /**
     * @brief Dealocates the memory from the texture
     * 
     */
    void free();

    // Methods
    /**
     * @brief Loads the texture from a given file
     * 
     * @param window The window in which the texture gonna be rendered
     * @param renderer The renderer which gonna render the texture
     * @param path The path to the file
     * @param alpha Flag to set to true if there is alpha in the texture
     * @return true in succes
     * @return false in faliure
     */
    bool loadFromFile(std::string path, bool alpha = false);

    bool createFromOtherTexture(cTexture& otherTexture, SDL_Rect* clip);

    /**
     * @brief Renders the texture to the screen
     * 
     * @param x The x position to render the texture to
     * @param y The y position to render the texture to
     * @param clip Facultative: a SDL_Rect which determines the part of the texture to render
     */
    void render(int x, int y, SDL_Rect* clip = NULL);

    /**
     * @brief Locks the texture to acces its pixels
     * 
     * @return true in succes
     * @return false in faliure or the texture is already locked
     */
    bool lockTexture(SDL_Rect* clip = NULL);

    /**
     * @brief Unlocks the texture
     * 
     * @return true succes
     * @return false if the texture was already unlocked
     */
    bool unlockTexture();

    // Accessors
    /**
     * @brief Get the width of the texture
     * 
     * @return int: the width of the texture
     */
    int get_width();

    /**
     * @brief Get the height of the texture
     * 
     * @return int: the height of the texture
     */
    int get_height();

    /**
     * @brief Get the Pixels array of the texture
     * 
     * @return void*: a pointer to the array of pixels
     */
    void* get_Pixels();

    /**
     * @brief Get the Pitch of the texture
     * 
     * @return int: the pitch of the texture
     */
    int get_Pitch();

private:
    // The texture
    SDL_Texture* m_texture;
    void* m_pixels;
    int m_pitch;
    Uint32 m_format;
    bool m_alpha;

    // Dimensins
    int m_width;
    int m_height;

    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
};

#endif