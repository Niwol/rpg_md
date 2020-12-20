#ifndef FIGHT_MANAGER_HPP
#define FIGHT_MANAGER_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dynamic.hpp"

class cFightManager
{
public:

    cFightManager();
    ~cFightManager();

private:

    std::vector<cDynamic*> m_dynamicVector;

    bool m_turnOver;
};

#endif // FIGHT_MANAGER_HPP