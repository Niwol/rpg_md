#include "inputManager.hpp"

cInputManager::cInputManager()
{
}

void cInputManager::handleInput(SDL_Event& e)
{
    switch (e.type) {
    case SDL_KEYDOWN: {
        switch (e.key.keysym.sym) {
        }
    } break;

    case SDL_KEYUP: {
        switch (e.key.keysym.sym) {
        }
    } break;
    }
}