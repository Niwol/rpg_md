#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "character.hpp"
#include "dynamic.hpp"
#include "gameObject.hpp"
#include "map.hpp"
#include "texture.hpp"

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

        cMap map(window, renderer, 20, 16);
        map.loadTileMap("files/assets/tilemaps/tilemap_nature.png", 10, 20, true);
        map.load("files/maps/test.map");

        cCharacter c(window, renderer, 2, 2);
        c.loadSpriteSheet("files/assets/characters/player.png");

        cDynamic dyn(window, renderer, 5, 4);
        dyn.load("files/dynamicObjects/characters/test.dyn");

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

                    case SDLK_z:
                        dyn.move(MOVE_UP, map);
                        break;

                    case SDLK_s:
                        dyn.move(MOVE_DOWN, map);
                        break;

                    case SDLK_q:
                        dyn.move(MOVE_LEFT, map);
                        break;

                    case SDLK_d:
                        dyn.move(MOVE_RIGHT, map);
                        break;
                    }
                }

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                }

                //c.handleEvent(e);
                map.handleEvent(e);
            }

            //c.move();
            dyn.update();

            // Rendering
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            map.render(550, 80);
            map.renderTilemap(10, 20);

            c.render(map);

            dyn.render(map);

            SDL_RenderPresent(renderer);

            c.nextFrame();
        }

        map.save("files/maps/test.map");
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

    *w = SDL_CreateWindow("RPG Test", 200,
        50, SCREEN_W, SCREEN_H,
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
