#pragma once
#include <vector>
#include <deque>
#include "world.h"
#include <cstdio>

/**
 * @class sine_generator
 * @brief Injects a sine wave signal into the world at a given position.
 *
 * Produces a sinusoidal disturbance centered at (x, y) with configurable aplitude, frequency, and phase.
 * The generator can be active over specified time range, or indefinitely if end < start.
 */
class sine_generator {
public:
    /**
     * @param w Reference to the world the generator affects
     * @param x X-coordinate of the injection point
     * @param y Y-coordinate of the injection point
     * @param amplitude Wave amplitude
     * @param frequency Frequency in 1/ticks
     * @param offset Phase offset in radians
     * @param start First time step the generator is active
     * @param end Last active step (use end < start for infinite duration)
     */
    sine_generator(world& w, int x, int y,
        float amplitude, float frequency, float offset,
        unsigned int start, unsigned int end);

    /**
     * @brief Apply the generator’s output at the given time step.
     */
    void operator()(world& w, int t);

private:
    int x, y;
    float amplitude, frequency, offset;
    unsigned int start, end;
};


/**
 * @class sawtooth_generator
 * @brief Produces a rising sawtooth waveform at a fixed position.
 */
class sawtooth_generator {
public:
    sawtooth_generator(world& w, int x, int y,
        float amplitude, float frequency, float offset,
        unsigned int start, unsigned int end);

    void operator()(world& w, int t);

private:
    int x, y;
    float amplitude, frequency, offset;
    unsigned int start, end;
};


/**
 * @class falling_sawtooth_generator
 * @brief Produces a falling (descending) sawtooth waveform at a fixed position.
 */
class falling_sawtooth_generator {
public:
    falling_sawtooth_generator(world& w, int x, int y,
        float amplitude, float frequency, float offset,
        unsigned int start, unsigned int end);

    void operator()(world& w, int t);

private:
    int x, y;
    float amplitude, frequency, offset;
    unsigned int start, end;
};


/**
 * @class square_generator
 * @brief Produces a square wave at a fixed position.
 */
class square_generator {
public:
    square_generator(world& w, int x, int y,
        float amplitude, float frequency, float offset,
        unsigned int start, unsigned int end);

    void operator()(world& w, int t);

private:
    int x, y;
    float amplitude, frequency, offset;
    unsigned int start, end;
};