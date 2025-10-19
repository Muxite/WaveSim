#include "world.h"
#include "calculate_wave_cuda.h"
#include <cuda_runtime.h>



__global__ void calculate_wave_kernel(const float* prev, const float* pres, float* futu, int rows, int cols, float speed)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	int x = idx % (cols + 2);
	int y = idx / (cols + 2);

	if (x == 0 || y == 0 || x == cols + 1 || y == rows + 1)
		return;

	int above = (y - 1) * (cols + 2) + x;
	int below = (y + 1) * (cols + 2) + x;
	int left = y * (cols + 2) + (x - 1);
	int right = y * (cols + 2) + (x + 1);

	futu[idx] = 2 * pres[idx] - prev[idx] + speed * (pres[above] + pres[below] + pres[left] + pres[right] - 4 * pres[idx]);
}


void calculate_wave_cuda_wrapper(const float* prev, const float* pres, float* futu, int rows, int cols, float speed)
{
	float* d_prev, * d_pres, * d_futu;

	size_t size = (size_t) ((rows + 2) * (cols + 2) * sizeof(float));

	cudaMalloc((void**)&d_prev, size);
	cudaMalloc((void**)&d_pres, size);
	cudaMalloc((void**)&d_futu, size);

	cudaMemcpy(d_prev, prev, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_pres, pres, size, cudaMemcpyHostToDevice);

	int num_elements = (rows + 2) * (cols + 2);
	int threads_per_block = 256;
	int blocks = (num_elements + threads_per_block - 1) / threads_per_block;

	calculate_wave_kernel <<<blocks, threads_per_block >>> (
		d_prev,
		d_pres,
		d_futu,
		rows,
		cols,
		speed
	);
	cudaDeviceSynchronize();
	cudaMemcpy(futu, d_futu, size, cudaMemcpyDeviceToHost);
	cudaFree(d_prev);
	cudaFree(d_pres);
	cudaFree(d_futu);
}