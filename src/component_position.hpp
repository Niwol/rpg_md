#ifndef COMPONENT_POSITION_HPP
#define COMPONENT_POSITION_HPP

struct sComponent_position {
    int x = 0, y = 0;
    enum directionEnum {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    directionEnum direction = directionEnum::DOWN;
};

#endif // COMPONENT_POSITION_HPP