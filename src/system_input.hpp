#ifndef SYSTEM_INPUT_HPP
#define SYSTEM_INPUT_HPP

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "component_key.hpp"
#include "system.hpp"

class cSystem_input : public cSystem {
public:
    cSystem_input();

    void handle_input(SDL_Event& e);

    void setComponent_key(std::shared_ptr<sComponent_key> component_key);

    // Not used
    void update(float deltaTime);

private:
    std::shared_ptr<sComponent_key> m_component_key;
};

#endif // SYSTEM_INPUT_HPP