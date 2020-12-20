#include "gameObject.hpp"

cGameObject::cGameObject(std::string name)
{
    m_name = name;
}

cGameObject::~cGameObject()
{
}

std::string cGameObject::get_name() { return m_name; }