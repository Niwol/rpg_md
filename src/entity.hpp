#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "compnentType.hpp"
#include <vector>

struct sEntity {
    int entityID;
    std::vector<sEntityComponent> components;
};

#endif // ENTITY_HPP