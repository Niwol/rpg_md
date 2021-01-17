#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "component_position.hpp"
#include "component_render.hpp"
#include "entity.hpp"
#include "inputManager.hpp"
#include "system_ai.hpp"
#include "system_render.hpp"

class cSceneManager {
public:
    cSceneManager(SDL_Window* window, SDL_Renderer* renderer);
    ~cSceneManager();

    void addEnemy(int x, int y);
    void addPlayer(int x, int y);

    void handleInput(SDL_Event& e);
    void update();
    void render();

private:
    // Entitys
    std::vector<sEntity> m_entitys;

    // Systems
    cSystem_ai m_system_ai;
    cSystem_render m_system_render;

    // Components
    std::map<id_t, std::shared_ptr<sComponent_position>> m_components_position;
    std::map<id_t, std::shared_ptr<sComponent_render>> m_components_render;

    // Attributes
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    cInputManager m_inputManager;
};

#endif // SCENE_MANAGER_HPP