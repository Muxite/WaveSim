#include "benchmark.h"

int main()
{
	BenchmarkResult basic = run_benchmark(UpdateMethod::Basic, 3840, 2160, 1024, false);
	BenchmarkResult cuda = run_benchmark(UpdateMethod::CUDA, 3840, 2160, 1024, false);

	print_benchmark_result(basic);
	print_benchmark_result(cuda);

    return 0;
}