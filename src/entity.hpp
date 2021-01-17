#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

#include "compnentType.hpp"

struct sEntity {
    id_t entityID;
    std::vector<sEntityComponent> components;
};

#endif // ENTITY_HPP