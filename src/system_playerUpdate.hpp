#ifndef SYSTEM_PLAYER_UPDATE
#define SYSTEM_PLAYER_UPDATE

#include <memory>

#include "component_key.hpp"
#include "component_position.hpp"
#include "system.hpp"

class cSystem_playerUpdate : public cSystem {
public:
    cSystem_playerUpdate();

    void update(float deltaTime);

    void setComponent(std::shared_ptr<sComponent_position> posComp, std::shared_ptr<sComponent_key> keyComp);

private:
    struct sComponents {
        std::shared_ptr<sComponent_position> position;
        std::shared_ptr<sComponent_key> key;
    };

    sComponents m_components;
};

#endif // SYSTEM_PLAYER_UPDATE