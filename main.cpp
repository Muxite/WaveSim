#include <SFML/Graphics.hpp>
#include "world.h"
#include "display.h"
#include "function_generator.h"
#include <random>
#include <chrono>
#include <iostream>

int main()
{
    const int upscale = 6;
    const int width = 1920/3;
    const int height = 1080/3;
    const int start_x = width / 4;
	const int end_x = 3 * width / 4;
	const int start_y = height / 4;
	const int end_y = 3 * height / 4;
    int frames = 0;

	std::chrono::duration<double, std::milli> total_update_time(0.0);
    std::chrono::duration<double, std::milli> total_draw_time(0.0);

    sf::RenderWindow window(sf::VideoMode({ upscale * (end_x - start_x), upscale * (end_y - start_y)}), "Wavesim");
    const float speed = 0.5f;
    world w(width, height, speed, false);


    w.add_generator(sine_generator(w, 3*width / 8, 2*height / 8, 300.0f, 0.0251f, 0.0f, 1, 120));
    w.add_generator(sine_generator(w, 4 * width / 8, 2 * height / 8, 300.0f, 0.0212f, 0.2f, 1, 120));
    w.add_generator(sine_generator(w, 5*width / 8, 2*height / 8, 300.0f, 0.02f, 0.423f, 1, 400));
    w.add_generator(sine_generator(w, 4 * width / 8, 5 * height / 8, 400.0f, 0.0111f, 0.3f, 150, 250));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        auto draw_start = std::chrono::high_resolution_clock::now();
        draw_world(window, w, upscale, start_x, end_x, start_y, end_y);
        auto draw_end = std::chrono::high_resolution_clock::now();

        auto update_start = std::chrono::high_resolution_clock::now();
        w.update();
        auto update_end = std::chrono::high_resolution_clock::now();

		total_draw_time += draw_end - draw_start;
		total_update_time += update_end - update_start;

        window.display();
        frames += 1;
		
    }

	auto average_draw_time = total_draw_time.count() / frames;
	auto average_update_time = total_update_time.count() / frames;
    std::cout << "Sim Width: " << width << ", Sim Height: " << height << "\n";
    std::cout << "Draw time: " << average_draw_time << " ms, Update time: " << average_update_time << " ms\n";

    return 0;
}