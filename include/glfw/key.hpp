#pragma once

#include <cmath>

namespace glfw {

struct key {
    int code;

    enum class action {
        release, press, repeat
    };

    enum class modifier {
        shift = 0b1, control = 0b10, alt = 0b100, super = 0b1000
    };
};

struct {
    static constexpr key space{32};
} keys;

}