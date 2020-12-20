#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <vector>

#include "positionComponent.hpp"
#include "renderComponent.hpp"
#include "system.hpp"

class cRenderSystem : public cSystem {

public:
    cRenderSystem(SDL_Window* window, SDL_Renderer* renderer);

    void addComponent(sRenderComponent* rendrerComp, sPositionComponent* posComp);
    void removeComponent(sRenderComponent* rendrerComp, sPositionComponent* posComp);

    void update(float deltaTime);

private:
    struct sComponents {
        sRenderComponent* renderComponent;
        sPositionComponent* positionComponent;
    };

    std::vector<sComponents> m_components;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif // RENDER_SYSTEM_HPP