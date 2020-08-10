#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "character.hpp"
#include "map.hpp"
#include "texture.hpp"

constexpr int SCREEN_W = 1900;
constexpr int SCREEN_H = 1000;

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

        cMap map(40, 30);
        map.loadTileMap(window, renderer,
            "files/assets/tilemaps/tilemap_nature.png", 10, 20, true);
        map.load("files/maps/test.map");

        cCharacter c;
        c.loadSpriteSheet(window, renderer, "files/assets/characters/player.png");

        cTexture t;
        t.loadFromFile(window, renderer, "files/assets/characters/set.png");

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

                c.handleEvent(e);
                map.handleEvent(e);
            }

            c.move();

            // Rendering
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            map.render(renderer, 550, 80);
            map.renderTilemap(renderer, 10, 20);

            c.render();

            t.render(100, 200);

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

    SDL_Rect rect;
    SDL_GetDisplayBounds(0, &rect);
    printf("x = %d\ny = %d\nw = %d\nh = %d\n", rect.x, rect.y, rect.w, rect.h);

    *w = SDL_CreateWindow("RPG Test", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, rect.w, rect.h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
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
