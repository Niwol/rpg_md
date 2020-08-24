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

        cMap map(window, renderer, 40, 30);
        map.loadTileMap("files/assets/tilemaps/tilemap_nature.png", 10, 20, true);
        map.load("files/maps/test.map");

        cCharacter c(window, renderer, 2, 2);
        c.loadSpriteSheet("files/assets/characters/player.png");

        cTexture t(window, renderer);
        t.loadFromFile("files/assets/characters/set.png");

        cGameObject o("Test");
        cDynamic d1(window, renderer, 2, 3);
        cDynamic d2(window, renderer, 5, 9);

        d1.loadSpriteSheet("files/assets/characters/player.png");
        d2.loadSpriteSheet("files/assets/characters/enemy.png");

        cRender render(window, renderer);
        render.load(window, renderer, "files/dynamicObjects/characters/test.dyn");

        cTexture texture(window, renderer);
        texture.loadFromFile("files/assets/characters/player.png", true);

        SDL_Rect clip = { 32, 32, 32 * 2, 32 * 2 };

        cTexture partialTexture(window, renderer);
        partialTexture.createFromOtherTexture(texture, &clip);
        printf("W = %d\nH = %d\n", partialTexture.get_width(), partialTexture.get_height());

        /*cTexture test(window, renderer);
        test.loadFromFile("files/testTexture.png", false);
        printf("Width = %d\nHeigth = %d\n", test.get_width(), test.get_height());

        Uint32* pixels;
        int pitch;

        test.lockTexture(&clip);

        pixels = (Uint32*)test.get_Pixels();
        pitch = test.get_Pitch();

        printf("pitch = %d\n", pitch);

        for (int i = 0; i < 12; i++) {
            printf("%8X ", pixels[i]);
            if ((i + 1) % 3 == 0)
                printf("\n");
        }

        test.unlockTexture();*/

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

            map.render(550, 80);
            map.renderTilemap(10, 20);

            c.render(map);

            t.render(100, 200);

            d1.render(map);
            d2.render(map);

            texture.render(100, 300);
            partialTexture.render(100, 500);

            //test.render(200, 500);

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
