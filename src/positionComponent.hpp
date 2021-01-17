#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

struct sPositionComponent {
    int x = 0, y = 0;
    enum directionEnum{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    directionEnum direction = directionEnum::DOWN;
};

#endif // POSITION_COMPONENT_HPP