#include <SFML/Graphics.hpp>
#include "world.h"
#include "display.h"
#include "function_generator.h"
#include <random>
#include <chrono>
#include <iostream>

int main()
{
    const int upscale = 8;
    const int width = 360;
    const int height = 225;
    sf::RenderWindow window(sf::VideoMode({ upscale * width, upscale * height }), "Wavesim");
    const float speed = 0.3f;
    world w(width, height, speed, true);

    for (int i = 2; i <= 6; i++)
    {
        w.add_generator(sine_generator(w, i * width / 8, i*height / 8, 60.0f, 0.02f, (float)(i) * 0.2));
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        auto draw_start = std::chrono::high_resolution_clock::now();
        draw_world(window, w, upscale);
        auto draw_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> draw_time = draw_end - draw_start;

        auto update_start = std::chrono::high_resolution_clock::now();
        w.update();
        auto update_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> update_time = update_end - update_start;

        window.display();

		std::cout << "Draw time: " << draw_time.count() << " ms, Update time: " << update_time.count() << " ms\n";
    }

    return 0;
}