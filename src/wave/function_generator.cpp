#include "function_generator.h"
#include <cmath>

sine_generator::sine_generator(world& w, int x, int y, float amplitude, float frequency, float offset, unsigned int start, unsigned int end)
    : x(x), y(y), amplitude(amplitude), frequency(frequency), offset(offset), start(start), end(end)
{
    w.add_generator([this](world& w, int t) {
        (*this)(w, t);
        });
}

void sine_generator::operator()(world& w, int t)
{
    if ((t > start && t < end) || end < start)
    {
        w.get(1, x, y) = amplitude * std::sin((frequency * t + offset) * 3.1415926f * 2.f);
    }
}

sawtooth_generator::sawtooth_generator(world& w, int x, int y, float amplitude, float frequency, float offset, unsigned int start, unsigned int end)
    : x(x), y(y), amplitude(amplitude), frequency(frequency), offset(offset), start(start), end(end)
{
    w.add_generator([this](world& w, int t) {
        (*this)(w, t);
        });
}

void sawtooth_generator::operator()(world& w, int t)
{
    if ((t > start && t < end) || end < start)
    {
        float phase = std::fmod(frequency * t + offset, 1.0f);
        if (phase < 0) phase += 1.0f;
        w.get(1, x, y) = amplitude * phase;
    }
}

falling_sawtooth_generator::falling_sawtooth_generator(world& w, int x, int y, float amplitude, float frequency, float offset, unsigned int start, unsigned int end)
    : x(x), y(y), amplitude(amplitude), frequency(frequency), offset(offset), start(start), end(end)
{
    w.add_generator([this](world& w, int t) {
        (*this)(w, t);
        });
}

void falling_sawtooth_generator::operator()(world& w, int t)
{
    if ((t > start && t < end) || end < start)
    {
        float phase = std::fmod(frequency * t + offset, 1.0f);
        if (phase < 0) phase += 1.0f;
        w.get(1, x, y) = amplitude * (1.0f - phase);
    }
}

square_generator::square_generator(world& w, int x, int y, float amplitude, float frequency, float offset, unsigned int start, unsigned int end)
    : x(x), y(y), amplitude(amplitude), frequency(frequency), offset(offset), start(start), end(end)
{
    w.add_generator([this](world& w, int t) {
        (*this)(w, t);
        });
}

void square_generator::operator()(world& w, int t)
{
    if ((t > start && t < end) || end < start)
    {
        float phase = std::fmod(frequency * t + offset, 1.0f);
        if (phase < 0) phase += 1.0f;
        w.get(1, x, y) = (phase < 0.5f) ? amplitude : -amplitude;
    }
}