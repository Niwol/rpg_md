#include "aiSystem.hpp"

cAiSystem::cAiSystem() { }

void cAiSystem::addComponenet(sPositionComponent* comp)
{
    m_posComponents.push_back(comp);
}

void cAiSystem::removeComponent(sPositionComponent* comp)
{
    // TODO
}

void cAiSystem::update(float deltaTime)
{
    for (long unsigned int i = 0; i < m_posComponents.size(); i++) {
        //printf("AI system update Comp #%4ld\n", i);
        m_posComponents[i]->x--;
        if (m_posComponents[i]->x <= 0)
            m_posComponents[i]->x = 1500;
    }

    //printf("AI system update DONE\n");
}