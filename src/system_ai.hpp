#ifndef SYSTEM_AI_HPP
#define SYSTEM_AI_HPP

#include <iostream>
#include <memory>
#include <vector>

#include "component_position.hpp"
#include "system.hpp"

class cSystem_ai : public cSystem {

public:
    cSystem_ai();

    void addComponenet(std::shared_ptr<sComponent_position> comp);
    void removeComponent(std::shared_ptr<sComponent_position> comp);

    void update(float deltaTime);

private:
    std::vector<std::shared_ptr<sComponent_position>> m_component_position;
};

#endif // SYSTEM_AI_HPP