#include "compnentType.hpp"

unsigned int getUnicID(int type, bool entity)
{
    static unsigned int nextID[TOTAL_COMPONENTS] = { 0 };
    static unsigned int nextEntityID = 0;

    if (entity)
        return nextEntityID++;
    else
        return nextID[type]++;
}

std::string getComponenetTypeString(int type)
{
    switch (type) {
    case POSITION_COMPONENT:
        return "POSITION_COMPONENT";
        break;

    case RENDER_COMPONENT:
        return "RENDER_COMPONENT";
        break;
    }

    return "";
}