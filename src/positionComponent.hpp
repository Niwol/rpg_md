#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

struct sPositionComponent {
    int x, y;
    enum {
        UP,
        DOWN,
        LEFT,
        RIGHT
    } direction;
};

#endif // POSITION_COMPONENT_HPP