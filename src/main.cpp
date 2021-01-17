#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sceneManager.hpp"

//#include "character.hpp"
//#include "dynamic.hpp"
//#include "gameObject.hpp"
//#include "map.hpp"
//#include "player.hpp"
//#include "texture.hpp"

constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

bool init(SDL_Window** w, SDL_Renderer** r);

/**
 * @brief Test
 * 
 * @return int 
 */
int main()
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    bool quit = false;

    if (!init(&window, &renderer)) {
        printf("Exiting...\n");
        exit(1);
    } else {
        SDL_Event e;

        cSceneManager manager(window, renderer);
        manager.addEnemy(500, 300);
        manager.addEnemy(600, 200);
        manager.addEnemy(300, 500);
        manager.addEnemy(400, 200);
        manager.addEnemy(800, 600);
        manager.addEnemy(900, 300);
        manager.addEnemy(850, 100);
        manager.addEnemy(700, 500);
        manager.addEnemy(600, 500);
        manager.addEnemy(750, 100);
        manager.addEnemy(900, 500);
        manager.addEnemy(200, 200);
        manager.addPlayer(100, 100);

        while (!quit) {
            // Events
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT)
                    quit = true;

                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                }

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                }

                manager.handleInput(e);
            }

            manager.update();

            // Rendering

            manager.render();
        }
    }

    // Dealocating memory
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    IMG_Quit();

    return 0;
}

bool init(SDL_Window** w, SDL_Renderer** r)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_ERROR: %s", SDL_GetError());
        return 0;
    }

    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("IMG could not initialize! IMG_ERROR: %s", IMG_GetError());
    }

    *w = SDL_CreateWindow("RPG Test",
        SDL_WINDOWPOS_UNDEFINED_DISPLAY(1), SDL_WINDOWPOS_UNDEFINED_DISPLAY(1),
        SCREEN_W, SCREEN_H,
        SDL_WINDOW_SHOWN);
    if (*w == NULL) {
        printf("Unable to create window! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }

    *r = SDL_CreateRenderer(*w, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*r == NULL) {
        printf("Unablel to create renderer! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
