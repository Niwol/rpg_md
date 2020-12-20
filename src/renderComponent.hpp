#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include <SDL2/SDL.h>

#include "texture.hpp"

struct sRenderComponent {
    cTexture texture;
    SDL_Rect clip;
};

#endif // RENDER_COMPONENT_HPP