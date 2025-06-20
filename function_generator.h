#pragma once
#include <vector>
#include <deque>
#include "world.h"

class sine_generator {
public:
    sine_generator(world& w, int x, int y, float amplitude, float frequency, float offset, unsigned int start, unsigned int end);

    // functor so we can call the class like a function
    void operator()(world& w, int t);

private:
    int x, y;
    float amplitude, frequency, offset;
    unsigned int start, end;
};