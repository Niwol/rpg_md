#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

class cGameObject {
public:
    /**
     * @brief Construct a new c Game Object object
     * 
     * @param name name of the object
     */
    cGameObject(std::string name = "Object");

    /**
     * @brief Destroy the c Game Object object
     * 
     */
    ~cGameObject();

    /**
     * @brief Get the name of the object
     * 
     * @return std::string: the name of the object
     */
    std::string get_name();

private:
    std::string m_name;
};

#endif