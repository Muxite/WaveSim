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


void draw_world(sf::RenderWindow& window, world& w, float upscale,
    int start_x = 0, int end_x = 9999, int start_y = 0, int end_y = 9999)
{
    if (upscale <= 0) upscale = 1;

    int world_w = end_x - start_x;
    int world_h = end_y - start_y;

    int draw_cols = static_cast<int>(world_w * std::max(upscale, 0.001f));
    int draw_rows = static_cast<int>(world_h * std::max(upscale, 0.001f));

    if (draw_cols <= 0 || draw_rows <= 0)
        return;

    float cell_size = 1.0f / upscale;

    sf::VertexArray grid(sf::PrimitiveType::Triangles, draw_rows * draw_cols * 6);
    int idx = 0;

    for (int y = 0; y < draw_rows; ++y) {
        for (int x = 0; x < draw_cols; ++x) {
            float wx_f = start_x + x / upscale;
            float wy_f = start_y + y / upscale;

            int wx = std::clamp(static_cast<int>(wx_f), start_x, end_x - 1);
            int wy = std::clamp(static_cast<int>(wy_f), start_y, end_y - 1);

            float value = w.get(1, wx, wy);
            sf::Color color = colorize(value, -100.0f, 100.0f);

            float px = static_cast<float>(x) * cell_size;
            float py = static_cast<float>(y) * cell_size;

            grid[idx + 0].position = { px, py };
            grid[idx + 1].position = { px + cell_size, py };
            grid[idx + 2].position = { px + cell_size, py + cell_size };

            grid[idx + 3].position = { px, py };
            grid[idx + 4].position = { px + cell_size, py + cell_size };
            grid[idx + 5].position = { px, py + cell_size };

            for (int i = 0; i < 6; ++i)
                grid[idx + i].color = color;

            idx += 6;
        }
    }

    window.draw(grid);
}
