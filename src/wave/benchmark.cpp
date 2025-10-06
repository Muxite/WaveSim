#include<benchmark.h>

BenchmarkResult run_benchmark(
    UpdateMethod update_method,
    int width,
    int height,
    int frame_count
) {

    int frames = 0;

    std::chrono::duration<double, std::milli> total_update_time(0.0);
    std::chrono::duration<double, std::milli> total_draw_time(0.0);

    sf::RenderWindow window(sf::VideoMode({ (unsigned int) width, (unsigned int) height }), "Wavesim");
    const float speed = 0.4f;
    world w(width, height, speed, false);


    w.add_generator(sine_generator(w, width / 3, 1 * height / 3, 64.0f, 0.0500f, 0.0f, 1, 99999));
    w.add_generator(sine_generator(w, 2 * width / 3, 2 * height / 3, 256.0f, 0.0200f, 0.0f, 1, 99999));

    while (window.isOpen() && frames < frame_count)
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        auto draw_start = std::chrono::high_resolution_clock::now();
        draw_world(window, w, 1, 0, width, 0, height);
        auto draw_end = std::chrono::high_resolution_clock::now();

        auto update_start = std::chrono::high_resolution_clock::now();
        switch (update_method)
        {
        case UpdateMethod::Basic:
            w.update();
            break;

        case UpdateMethod::Parallel:
            w.update_parallel();
            break;

        default:
            w.update();
            break;
        }
        w.update();
        auto update_end = std::chrono::high_resolution_clock::now();

        total_draw_time += draw_end - draw_start;
        total_update_time += update_end - update_start;

        window.display();
        frames += 1;

    }

    auto average_draw_time = total_draw_time.count() / frames;
    auto average_update_time = total_update_time.count() / frames;

    return BenchmarkResult{ average_update_time, average_draw_time, frames };
}

void print_benchmark_result(const BenchmarkResult & result) {
    std::cout << "************************************\n";
    std::cout << "Frames: " << result.frames << "\n";
    std::cout << "Update: " << result.average_update_time << " ms/frame\n";
    std::cout << "Draw: " << result.average_draw_time << " ms/frame\n";
    std::cout << "Total: " << result.average_update_time + result.average_draw_time << " ms/frame\n";
    std::cout << "************************************\n";
}