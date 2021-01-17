#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "aiSystem.hpp"
#include "entity.hpp"
#include "inputManager.hpp"
#include "positionComponent.hpp"
#include "renderComponent.hpp"
#include "renderSystem.hpp"

class cSceneManager {
public:
    cSceneManager(SDL_Window* window, SDL_Renderer* renderer);
    ~cSceneManager();

    void addEnemy(int x, int y);

    void handleInput(SDL_Event& e);
    void update();
    void render();

private:
    // Entitys
    std::vector<sEntity> m_entitys;

    // Systems
    cAiSystem m_aiSystem;
    cRenderSystem m_renderSystem;

    // Components
    std::map<id_t, std::shared_ptr<sPositionComponent>> m_posComponents;
    std::map<id_t, std::shared_ptr<sRenderComponent>> m_renderComponents;

    // Attributes
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    cInputManager m_inputManager;
};

#endif // SCENE_MANAGER_HPP