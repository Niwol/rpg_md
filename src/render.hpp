#ifndef RENDER_HPP
#define RENDER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.hpp"

struct sAnimation {
    sAnimation(SDL_Window* window, SDL_Renderer* renderer, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight, int xOff, int yOff);

    int framesPerClip;
    int numberOfClips;
    int clipWidth;
    int clipHeigth;
    int xOff;
    int yOff;

    cTexture spriteSheet;
};

class cRender {
public:
    cRender(SDL_Window* window, SDL_Renderer* renderer);
    ~cRender();

    bool load(std::string path);

    void render(int x, int y);

    void startAnimation(int nAnimation);
    void restartAnimation();
    void pauseAnimation(bool set);
    void stopAnimation();
    void nextFrame();

    void set_animation(int nAimation, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    bool m_pause;
    int m_currentFrame;
    int m_nCurrentAnimation;
    sAnimation* m_currentAnimation;
    int m_numberOfAnimations;

    std::vector<sAnimation*> m_animations;
};

#endif