#ifndef COMPONENT_KEY_HPP
#define COMPONENT_KEY_HPP

struct sComponent_key {
    enum keyEnum {
        KEY_Z,
        KEY_Q,
        KEY_S,
        KEY_D,

        KEY_SPACE,

        TOTAL_KEY
    };

    bool keyHold[keyEnum::TOTAL_KEY];

    // Priority shit
};

#endif // COMPONENT_KEY_HPP