#include "system_render.hpp"

cSystem_render::cSystem_render(SDL_Window* window, SDL_Renderer* renderer)
    : m_window(window)
    , m_renderer(renderer)
{
}

void cSystem_render::addComponent(std::shared_ptr<sComponent_render> rendrerComp, std::shared_ptr<sComponent_position> posComp)
{
    m_components.push_back({ rendrerComp, posComp });
}

void cSystem_render::removeComponent(std::shared_ptr<sComponent_render> rendrerComp, std::shared_ptr<sComponent_position> posComp)
{
    // TODO
}

void cSystem_render::update(float deltaTime)
{
    SDL_SetRenderDrawColor(m_renderer, 51, 51, 51, 255);
    SDL_RenderClear(m_renderer);

    // Render map

    // Render entitys
    for (long unsigned int i = 0; i < m_components.size(); i++) {
        int x, y;
        SDL_Rect* clip;

        x = m_components[i].component_position->x;
        y = m_components[i].component_position->y;

        clip = &(m_components[i].component_render->clip);

        m_components[i].component_render->texture.render(x, y, clip);
    }

    SDL_RenderPresent(m_renderer);

    //printf("Render system update DONE\n");
}