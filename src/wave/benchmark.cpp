#include<benchmark.h>
#include <iomanip>

BenchmarkResult run_benchmark(
    UpdateMethod update_method,
    int width,
    int height,
    int frame_count,
    bool displayless
) {

    int frames = 0;

    std::chrono::duration<double, std::milli> total_update_time(0.0);
    std::chrono::duration<double, std::milli> total_draw_time(0.0);

    sf::RenderWindow window(sf::VideoMode({ (unsigned int) width, (unsigned int) height }), "WaveSim");
    const float speed = 0.4f;
	const float upscale = 0.0625f;
    world w(width, height, speed, update_method);


    w.add_generator(sine_generator(w, width / 3, 1 * height / 3, 64.0f, 0.0500f, 0.0f, 1, 99999));
    w.add_generator(sine_generator(w, 2 * width / 3, 2 * height / 3, 256.0f, 0.0200f, 0.0f, 1, 99999));
    w.add_generator(sine_generator(w, 2 * width / 3, 1 * height / 3, 256.0f, 0.1f, 0.0f, 1, 99999));

    while (frames < frame_count)
    {   
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        auto draw_start = std::chrono::high_resolution_clock::now();
        if (!displayless) 
        {
            draw_world(window, w, upscale, 0, width, 0, height);
            
        }
        auto draw_end = std::chrono::high_resolution_clock::now();

        auto update_start = std::chrono::high_resolution_clock::now();

        w.update();

        auto update_end = std::chrono::high_resolution_clock::now();

        total_draw_time += draw_end - draw_start;
        total_update_time += update_end - update_start;

        if (!displayless)
        {
            window.display();
        }
        
        frames += 1;

    }

    auto average_draw_time = total_draw_time.count() / frames;
    auto average_update_time = total_update_time.count() / frames;

    return BenchmarkResult{
        average_update_time,
        average_draw_time,
        frames,
        width, height,
        displayless ? 0 : (int)(width * upscale),
        displayless ? 0 : (int)(height * upscale),
        update_method
    };
}

void print_benchmark_result(const BenchmarkResult& result) {
    using std::cout;
    using std::setw;
    using std::left;
    using std::right;
    using std::setprecision;
    using std::fixed;

    cout << "\n========================================\n";
    cout << "   BENCHMARK RESULTS\n";
    cout << "========================================\n";
    cout << left << setw(20) << "Method:" << right << update_method_to_string(result.method) << "\n";
    cout << left << setw(20) << "Simulation Size:" << right << result.sim_width << " x " << result.sim_height << "\n";
    if (result.display_width > 0 && result.display_height > 0)
        cout << left << setw(20) << "Display Size:" << right << result.display_width << " x " << result.display_height << "\n";
    cout << left << setw(20) << "Frames:" << right << result.frames << "\n";
    cout << "----------------------------------------\n";

    cout << std::fixed << std::setprecision(3);
    cout << left << setw(20) << "Update Time:" << right << result.average_update_time << " ms/frame\n";
    cout << left << setw(20) << "Draw Time:" << right << result.average_draw_time << " ms/frame\n";
    cout << left << setw(20) << "Total Time:" << right << (result.average_update_time + result.average_draw_time) << " ms/frame\n";

    cout << "========================================\n\n";
}