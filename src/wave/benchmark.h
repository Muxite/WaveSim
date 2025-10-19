#include <SFML/Graphics.hpp>
#include "world.h"
#include "display.h"
#include "function_generator.h"
#include <chrono>
#include <vector>
#include <iostream>

/**
 * Performance metrics for benchmark runs
 */
struct BenchmarkResult {
    double average_update_time;
    double average_draw_time;
    int frames;
    int sim_width;
    int sim_height;
    int display_width;
    int display_height;
    UpdateMethod method;
};

/**
 * Prints benchmark results with simple formatting
 * @param result The benchmark results to display
 */
void print_benchmark_result(const BenchmarkResult& result);

/**
 * Runs wave simulation benchmark
 *
 * @param width : Screen/world width in pixels
 * @param height : Screen/world height in pixels
 * @param frame_count : Target frames to benchmark
 * @param update_method : World update method to benchmark
 * @return Performance metrics for update and draw operations
 *
 * Creates window with two sine wave generators and measures performance until window is closed.
 */
BenchmarkResult run_benchmark(
    UpdateMethod update_method = UpdateMethod::Basic,
    int width = 400,
    int height = 300,
    int frame_count = 1024,
	bool displayless = false
);