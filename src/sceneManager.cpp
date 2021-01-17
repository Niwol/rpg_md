#include "sceneManager.hpp"

cSceneManager::cSceneManager(SDL_Window* window, SDL_Renderer* renderer)
    : m_aiSystem()
    , m_renderSystem(window, renderer)
    , m_window(window)
    , m_renderer(renderer)
{
}

cSceneManager::~cSceneManager()
{
}

void cSceneManager::addEnemy(int x, int y)
{
    std::shared_ptr<sPositionComponent> posComp = std::make_shared<sPositionComponent>();
    std::shared_ptr<sRenderComponent> renderComp = std::make_shared<sRenderComponent>();

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
    m_posComponents.insert(std::pair<id_t, std::shared_ptr<sPositionComponent>>(compID, posComp));

    compType = RENDER_COMPONENT;
    compID = getUnicID(RENDER_COMPONENT);
    ent.components.push_back({ compType, compID });
    m_renderComponents.insert(std::pair<id_t, std::shared_ptr<sRenderComponent>>(compID, renderComp));

    m_aiSystem.addComponenet(posComp);
    m_renderSystem.addComponent(renderComp, posComp);

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

void cSceneManager::handleInput(SDL_Event& e)
{
    m_inputManager.handleInput(e);
}

void cSceneManager::update()
{
    m_aiSystem.update(0.0);
}

void cSceneManager::render()
{
    m_renderSystem.update(0.0);
}