#ifndef AI_SYSTEM_HPP
#define AI_SYSTEM_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "positionComponent.hpp"
#include "system.hpp"

class cAiSystem : public cSystem {

public:
    cAiSystem();

    void addComponenet(std::shared_ptr<sPositionComponent> comp);
    void removeComponent(std::shared_ptr<sPositionComponent> comp);

    void update(float deltaTime);

private:
    std::vector<std::shared_ptr<sPositionComponent>> m_posComponents;
};

#endif // AI_SYSTEM_HPP