#include "renderSystem.hpp"

cRenderSystem::cRenderSystem(SDL_Window* window, SDL_Renderer* renderer)
    : m_window(window)
    , m_renderer(renderer)
{
}

void cRenderSystem::addComponent(std::shared_ptr<sRenderComponent> rendrerComp, std::shared_ptr<sPositionComponent> posComp)
{
    m_components.push_back({ rendrerComp, posComp });
}

void cRenderSystem::removeComponent(std::shared_ptr<sRenderComponent> rendrerComp, std::shared_ptr<sPositionComponent> posComp)
{
    // TODO
}

void cRenderSystem::update(float deltaTime)
{
    SDL_SetRenderDrawColor(m_renderer, 51, 51, 51, 255);
    SDL_RenderClear(m_renderer);

    for (long unsigned int i = 0; i < m_components.size(); i++) {
        int x, y;
        SDL_Rect* clip;

        x = m_components[i].positionComponent->x;
        y = m_components[i].positionComponent->y;

        clip = &(m_components[i].renderComponent->clip);

        m_components[i].renderComponent->texture.render(x, y, clip);
    }

    SDL_RenderPresent(m_renderer);

    //printf("Render system update DONE\n");
}