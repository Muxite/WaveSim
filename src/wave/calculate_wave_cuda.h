#ifndef VECTOR_ADD_H
#define VECTOR_ADD_H

#ifdef __cplusplus
extern "C" {
#endif

void calculate_wave_cuda_wrapper(const float* prev, const float* pres, float* futu, int rows, int cols, float speed);

#ifdef __cplusplus
}
#endif

#endif
