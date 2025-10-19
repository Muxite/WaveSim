# WaveSim
A 2D wave simulation program using the discrete wave equation. Mainly in C++, with a small CUDA section. Uses CMake and SFML graphics.

https://github.com/user-attachments/assets/3d844cf4-4ba5-439e-b296-aa42474a4fe3

Features different methods for calculating each frame for different systems and to compare performance optimizations.
GPU acceleration increased speeds by 39x compared to threaded CPU computation. (RTX4050 vs Ryzen 7 8845HS)

## Current Methods
1. Compiler Automatic Parallelization (CPU)
2. CUDA (GPU)

<img width="852" height="850" alt="Screenshot 2025-10-16 212546" src="https://github.com/user-attachments/assets/94271c97-6936-44e5-9bde-9a7e52683608" />
