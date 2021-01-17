#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <vector>
#include <memory>

#include "positionComponent.hpp"
#include "renderComponent.hpp"
#include "system.hpp"

class cRenderSystem : public cSystem {

public:
    cRenderSystem(SDL_Window* window, SDL_Renderer* renderer);

    void addComponent(std::shared_ptr<sRenderComponent> rendrerComp, std::shared_ptr<sPositionComponent> posComp);
    void removeComponent(std::shared_ptr<sRenderComponent> rendrerComp, std::shared_ptr<sPositionComponent> posComp);

    void update(float deltaTime);

private:
    struct sComponents {
        std::shared_ptr<sRenderComponent> renderComponent;
        std::shared_ptr<sPositionComponent> positionComponent;
    };

    std::vector<sComponents> m_components;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif // RENDER_SYSTEM_HPP