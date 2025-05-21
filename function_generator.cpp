#include <vector>
#include <deque>
#include "world.h"
#include "function_generator.h"
#include <stdio.h>

sine_generator::sine_generator(world& w, int x, int y, float amplitude, float frequency, float offset)
    : x(x), y(y), amplitude(amplitude), frequency(frequency), offset(offset)
{

    // run add gen on init as a lambda that runs the functor.
    w.add_generator([this](world& w, int t) {
        (*this)(w, t);
        });
}

void sine_generator::operator()(world& w, int t)
{
    w.get(1, x, y) = amplitude * std::sin((frequency * t + offset) * 3.1415926f*2.f);
}