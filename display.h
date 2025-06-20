#pragma once
#include <vector>
#include <deque>
#include "world.h"
#include <SFML/Graphics.hpp>

sf::Color colorize(float value, float min, float max);
void display_print(const std::vector<std::vector<float>>& map);
void draw_world(sf::RenderWindow& window, world& w, int upscale, int start_x, int end_x, int start_y, int end_y);