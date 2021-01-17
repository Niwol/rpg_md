#ifndef COMPONENT_TYPE_HPP
#define COMPONENT_TYPE_HPP

#include <string>

enum componentType {
    POSITION_COMPONENT,
    RENDER_COMPONENT,
    TOTAL_COMPONENTS
};

struct sEntityComponent {
    int componentType;
    id_t componentID;
};

id_t getUnicID(int type, bool entity = false);
std::string getComponenetTypeString(int type);

#endif // COMPONENT_TYPE_HPP