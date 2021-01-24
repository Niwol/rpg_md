#include "system_input.hpp"

cSystem_input::cSystem_input() { }

void cSystem_input::handle_input(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_z:
            m_component_key->keyHold[sComponent_key::KEY_Z] = true;
            break;

        case SDLK_q:
            m_component_key->keyHold[sComponent_key::KEY_Q] = true;
            break;

        case SDLK_s:
            m_component_key->keyHold[sComponent_key::KEY_S] = true;
            break;

        case SDLK_d:
            m_component_key->keyHold[sComponent_key::KEY_D] = true;
            break;

        case SDLK_SPACE:
            m_component_key->keyHold[sComponent_key::KEY_SPACE] = true;
            break;
        }
    }

    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_z:
            m_component_key->keyHold[sComponent_key::KEY_Z] = false;
            break;

        case SDLK_q:
            m_component_key->keyHold[sComponent_key::KEY_Q] = false;
            break;

        case SDLK_s:
            m_component_key->keyHold[sComponent_key::KEY_S] = false;
            break;

        case SDLK_d:
            m_component_key->keyHold[sComponent_key::KEY_D] = false;
            break;

        case SDLK_SPACE:
            m_component_key->keyHold[sComponent_key::KEY_SPACE] = false;
            break;
        }
    }

    printf("INPUT SYSTEM: update\n");

    for (int i = 0; i < sComponent_key::TOTAL_KEY; i++) {
        printf("kay %d == %s\n", i, m_component_key->keyHold[i] ? "true" : "false");
    }
}

void cSystem_input::setComponent_key(std::shared_ptr<sComponent_key> component_key)
{
    m_component_key = component_key;
}

void cSystem_input::update(float deltaTime = 0.0f) { }