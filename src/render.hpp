#ifndef RENDER_HPP
#define RENDER_HPP

#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.hpp"

struct sAnimation {
    sAnimation(SDL_Window* window, SDL_Renderer* renderer);

    int framesPerClip;
    int numberOfClips;
    int clipWidth;
    int clipHeigth;

    cTexture spriteSheet;
};

class cRender {
public:
    cRender(SDL_Window* window, SDL_Renderer* renderer);
    ~cRender();

    bool load(SDL_Window* window, SDL_Renderer* renderer, std::string path);

    void render(int x, int y);

    void set_animation(int nAimation, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight);

private:
    SDL_Renderer* m_renderer;

    int m_currentFrame;
    int m_numberOfAnimations;

    sAnimation* m_animations;

    cTexture m_spriteSheet;
};

#endif