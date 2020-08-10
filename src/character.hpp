#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <iostream>

#include "texture.hpp"

enum stats {
    IDLE,
    WALKING
};

enum faceDirection {
    NO_DIRECTION = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

class cCharacter {
public:
    /**
     * @brief Construct a new c Character object
     * 
     */
    cCharacter();

    /**
     * @brief Destroy the c Character object
     * 
     */
    ~cCharacter();

    /**
     * @brief Loads the characters sprite sheet
     * 
     * @param window The window in which the character will be rendert
     * @param renderer The renderer which renders the character
     * @param path The path to the sprite sheet
     * @return true in succes
     * @return false in faliure
     */
    bool loadSpriteSheet(SDL_Window* window, SDL_Renderer* renderer, std::string path);

    /**
     * @brief Renders the character on its current xy position and with the apropriated sprite
     * 
     */
    void render();

    /**
     * @brief Handels the event from the user input
     * 
     * @param e The event to handle
     */
    void handleEvent(SDL_Event& e);

    /**
     * @brief If current stat is WALKING: makes the character move in the direction he is facing
     * 
     */
    void move();

    /**
     * @brief Increments current frame count, if current frame is the maximum of the current stat, it resets to 0
     * 
     */
    void nextFrame();

private:
    float m_x, m_y;
    float m_speed;

    int m_currentState;
    int m_currentFrame;
    int m_faceDirection;

    bool m_keyHeld[5];

    cTexture m_mainSpriteSheet;
};

#endif