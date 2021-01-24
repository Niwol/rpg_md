#ifndef SYSTEM_RENDER_HPP
#define SYSTEM_RENDER_HPP

#include <memory>
#include <vector>

#include "component_position.hpp"
#include "component_render.hpp"
#include "system.hpp"

class cSystem_render : public cSystem {

public:
    cSystem_render(SDL_Window* window, SDL_Renderer* renderer);

    void addComponent(std::shared_ptr<sComponent_render> rendrerComp, std::shared_ptr<sComponent_position> posComp);
    void removeComponent(std::shared_ptr<sComponent_render> rendrerComp, std::shared_ptr<sComponent_position> posComp);

    void update(float deltaTime);

private:
    struct sComponents {
        std::shared_ptr<sComponent_render> component_render;
        std::shared_ptr<sComponent_position> component_position;
    };

    std::vector<sComponents> m_components;
    //map map;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif // SYSTEM_RENDER_HPP