#include "benchmark.h"

int main()
{
	BenchmarkResult basic = run_benchmark(UpdateMethod::Basic);
	BenchmarkResult parallel = run_benchmark(UpdateMethod::Parallel);

	print_benchmark_result(basic);
	print_benchmark_result(parallel);

    return 0;
}