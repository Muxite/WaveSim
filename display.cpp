#include <iostream>
#include <vector>
#include <iomanip>
#include <SFML/Graphics.hpp>    
#include "world.h"

sf::Color colorize(float value, float min, float max)
{
    // Normalize and clamp the value to [-1, 1] based on the maximum absolute bound
    float range = std::max(std::abs(min), std::abs(max));
    float normalized = std::clamp(value / range, -1.0f, 1.0f);

    const sf::Color blue{ 0, 0, 255};
    const sf::Color gray{ 0, 0, 0 };
    const sf::Color red{ 255, 0, 0};

    auto lerp = [](const sf::Color& a, const sf::Color& b, float t) -> sf::Color {
        return {
            static_cast<uint8_t>(a.r + t * (b.r - a.r)),
            static_cast<uint8_t>(a.g + t * (b.g - a.g)),
            static_cast<uint8_t>(a.b + t * (b.b - a.b))
        };
        };

    if (normalized < 0.0f)
        return lerp(blue, gray, normalized + 1.0f);
    else
        return lerp(gray, red, normalized);
}


void display_print(const std::vector<std::vector<float>>& map)
{
	for (const auto& row : map)
	{
		for (auto value : row)
		{
			std::cout << std::setw(4) << (int)value;
		}
		std::cout << "\n";
		std::cout << "\n";
	}
}


void draw_world(sf::RenderWindow& window, world& w, int upscale, int start_x = 0, int end_x = 9999, int start_y = 0, int end_y = 9999) {
    sf::VertexArray grid(sf::PrimitiveType::Triangles, w.rows * w.cols * 6);

    int idx = 0;
    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            float value = w.get(1, x, y);
            sf::Color color = colorize(value, -100.0f, 100.0f);

            float px = (x - start_x) * upscale;
            float py = (y - start_y) * upscale;
            float ux = upscale;

            grid[idx + 0].position = { px, py };
            grid[idx + 1].position = { px + ux, py };
            grid[idx + 2].position = { px + ux, py + ux };

            grid[idx + 3].position = { px, py };
            grid[idx + 4].position = { px + ux, py + ux };
            grid[idx + 5].position = { px, py + ux };

            for (int i = 0; i < 6; ++i) {
                grid[idx + i].color = color;
            }

            idx += 6;
        }
    }

    window.draw(grid);
}
