#include "system_playerUpdate.hpp"

cSystem_playerUpdate::cSystem_playerUpdate() { }

void cSystem_playerUpdate::update(float deltaTime)
{
    if (m_components.key->keyHold[sComponent_key::KEY_Z])
        m_components.position->y -= 2;
    if (m_components.key->keyHold[sComponent_key::KEY_S])
        m_components.position->y += 2;
    if (m_components.key->keyHold[sComponent_key::KEY_Q])
        m_components.position->x -= 2;
    if (m_components.key->keyHold[sComponent_key::KEY_D])
        m_components.position->x += 2;
}

void cSystem_playerUpdate::setComponent(std::shared_ptr<sComponent_position> posComp, std::shared_ptr<sComponent_key> keyComp)
{
    m_components.position = posComp;
    m_components.key = keyComp;
}
