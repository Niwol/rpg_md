#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <SDL2/SDL.h>

class cInputManager {
public:
    cInputManager();

    void handleInput(SDL_Event& e);

private:
};

#endif // INPUT_MANAGER_HPP