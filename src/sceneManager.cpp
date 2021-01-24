#include "sceneManager.hpp"

cSceneManager::cSceneManager(SDL_Window* window, SDL_Renderer* renderer)
    : m_system_ai()
    , m_system_render(window, renderer)
    , m_system_input()
    , m_system_playerUpdate()
    , m_window(window)
    , m_renderer(renderer)
{
}

cSceneManager::~cSceneManager()
{
}

void cSceneManager::loadMap()
{
}

void cSceneManager::addEnemy(int x, int y)
{
    std::shared_ptr<sComponent_position> posComp = std::make_shared<sComponent_position>();
    std::shared_ptr<sComponent_render> renderComp = std::make_shared<sComponent_render>();

    renderComp->texture.init(m_window, m_renderer);
    renderComp->texture.loadFromFile("files/assets/characters/enemy.png", true);
    renderComp->clip = { 0, 0, 32, 32 };

    posComp->x = x;
    posComp->y = y;

    int compType;
    id_t compID;

    sEntity ent;
    ent.entityID = getUnicID(0, true);

    compType = POSITION_COMPONENT;
    compID = getUnicID(POSITION_COMPONENT);
    ent.components.push_back({ compType, compID });
    m_components_position.insert(std::pair<id_t, std::shared_ptr<sComponent_position>>(compID, posComp));

    compType = RENDER_COMPONENT;
    compID = getUnicID(RENDER_COMPONENT);
    ent.components.push_back({ compType, compID });
    m_components_render.insert(std::pair<id_t, std::shared_ptr<sComponent_render>>(compID, renderComp));

    m_system_ai.addComponenet(posComp);
    m_system_render.addComponent(renderComp, posComp);

    printf("Adding enemy entity:\n");
    printf("entityID = %d\n", ent.entityID);
    printf("Components:\n\n");
    for (unsigned int i = 0; i < ent.components.size(); i++) {

        printf("Component type = %s\n", getComponenetTypeString(ent.components[i].componentType).c_str());
        printf("Component ID = %d\n\n", ent.components[i].componentID);
    }
    printf("\n");

    m_entitys.push_back(ent);
}

void cSceneManager::addPlayer(int x, int y)
{
    // Components
    std::shared_ptr<sComponent_position> newPosComp = std::make_shared<sComponent_position>();
    std::shared_ptr<sComponent_render> newRenderComp = std::make_shared<sComponent_render>();
    std::shared_ptr<sComponent_key> newKeyComp = std::make_shared<sComponent_key>();
    sEntity newEntity;
    id_t posCompID, renderCompID, keyCompID;

    newPosComp->x = x;
    newPosComp->y = y;
    newPosComp->direction = sComponent_position::DOWN;
    posCompID = getUnicID(POSITION_COMPONENT);
    m_components_position.insert(std::pair<id_t, std::shared_ptr<sComponent_position>>(posCompID, newPosComp));

    newRenderComp->texture.init(m_window, m_renderer);
    newRenderComp->texture.loadFromFile("files/assets/characters/player.png", true);
    newRenderComp->clip = { 0, 0, 32, 32 };
    renderCompID = getUnicID(RENDER_COMPONENT);
    m_components_render.insert(std::pair<id_t, std::shared_ptr<sComponent_render>>(renderCompID, newRenderComp));

    for (int i = 0; i < sComponent_key::TOTAL_KEY; i++)
        newKeyComp->keyHold[i] = false;
    keyCompID = getUnicID(KEY_COMPONENT);
    m_component_key = newKeyComp;

    // Systems
    m_system_render.addComponent(newRenderComp, newPosComp);
    m_system_input.setComponent_key(newKeyComp);
    m_system_playerUpdate.setComponent(newPosComp, newKeyComp);

    // Entity
    newEntity.entityID = getUnicID(0, true);
    newEntity.components.push_back({ POSITION_COMPONENT, posCompID });
    newEntity.components.push_back({ RENDER_COMPONENT, renderCompID });
    newEntity.components.push_back({ KEY_COMPONENT, keyCompID });
    m_entitys.push_back(newEntity);
}

void cSceneManager::handleInput(SDL_Event& e)
{
    m_system_input.handle_input(e);
}

void cSceneManager::update()
{
    m_system_playerUpdate.update(0.0f);
    m_system_ai.update(0.0f);
}

void cSceneManager::render()
{
    m_system_render.update(0.0f);
}