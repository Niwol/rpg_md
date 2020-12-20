#ifndef AI_SYSTEM_HPP
#define AI_SYSTEM_HPP

#include <iostream>
#include <vector>

#include "positionComponent.hpp"
#include "system.hpp"

class cAiSystem : public cSystem {

public:
    cAiSystem();

    void addComponenet(sPositionComponent* comp);
    void removeComponent(sPositionComponent* comp);

    void update(float deltaTime);

private:
    std::vector<sPositionComponent*> m_posComponents;
};

#endif // AI_SYSTEM_HPP