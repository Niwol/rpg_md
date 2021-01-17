#include "system_ai.hpp"

cSystem_ai::cSystem_ai() { }

void cSystem_ai::addComponenet(std::shared_ptr<sComponent_position> comp)
{
    m_component_position.push_back(comp);
}

void cSystem_ai::removeComponent(std::shared_ptr<sComponent_position> comp)
{
    // TODO
}

void cSystem_ai::update(float deltaTime)
{
    for (long unsigned int i = 0; i < m_component_position.size(); i++) {
        //printf("AI system update Comp #%4ld\n", i);
        m_component_position[i]->x--;
        if (m_component_position[i]->x <= 0)
            m_component_position[i]->x = 1500;
    }

    //printf("AI system update DONE\n");
}