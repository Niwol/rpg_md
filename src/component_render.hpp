#ifndef COMPONENT_RENDER_HPP
#define COMPONENT_RENDER_HPP

#include <SDL2/SDL.h>

#include "texture.hpp"

struct sComponent_render {
    cTexture texture;
    SDL_Rect clip;
};

#endif // COMPONENT_RENDER_HPP