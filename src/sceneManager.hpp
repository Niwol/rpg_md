#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <iostream>
#include <map>
#include <vector>

#include "aiSystem.hpp"
#include "entity.hpp"
#include "positionComponent.hpp"
#include "renderComponent.hpp"
#include "renderSystem.hpp"

class cSceneManager {
public:
    cSceneManager(SDL_Window* window, SDL_Renderer* renderer);
    ~cSceneManager();

    void addEnemy(int x, int y);

    void update();
    void render();

private:
    // Entitys
    std::vector<sEntity> m_entitys;

    // Systems
    cAiSystem m_aiSystem;
    cRenderSystem m_renderSystem;

    // Components
    std::map<unsigned int, sPositionComponent*> m_posComponents;
    std::map<unsigned int, sRenderComponent*> m_renderComponents;

    // Attributes
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif // SCENE_MANAGER_HPP