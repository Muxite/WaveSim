#pragma once
#include <vector>
#include <functional>
#include <array>

// better memory version of world class. 
class world {
private:
    float speed;

public:
    int rows, cols;
    uint32_t time_index = 0;
    world(int r, int c, float s, bool wrap);
    bool wrap;
    float& get(uint8_t t, int x, int y);
    float lap(uint8_t t, int x, int y);
    void update();
    std::array<std::vector<float>, 3> map;
    std::vector<std::function<void(world&, int)>> generators;
    void add_generator(std::function<void(world&, int)> generator);
};
