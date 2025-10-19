#pragma once
#include <vector>
#include <deque>
#include "world.h"
#include <SFML/Graphics.hpp>

sf::Color colorize(float value, float min, float max);
void display_print(const std::vector<std::vector<float>>& map);

/**
 * @brief use SFML to draw the wave simulation world to the given window
 * @param window SFML RenderWindow to draw to
 * @param w World object containing simulation data
 * @param upscale Pixel scaling factor for display
 * @param start_x Starting x coordinate in the world to draw
 * @param end_x Ending x coordinate in the world to draw
 * @param start_y Starting y coordinate in the world to draw
 * @param end_y Ending y coordinate in the world to draw
 */
void draw_world(sf::RenderWindow& window, world& w, float upscale, int start_x, int end_x, int start_y, int end_y);