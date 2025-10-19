#pragma once
#include <vector>
#include <functional>
#include <array>
#include <string>

/**
 * Available world update implementations
 */
enum class UpdateMethod {
    Basic,
    Parallel,
    CUDA
};

std::string update_method_to_string(UpdateMethod method);

/**
 * @class world
 * @brief A 2D wave simulation implementing the wave equation using triple buffering
 *
 * This class simulates wave propagation on a 2D grid using the discrete form of the wave equation:
 * u(t+1) = 2*u(t) - u(t-1) + c^2 * n2u(t)
 *
 * The simulation uses triple buffering to store three time steps (t-1, t, t+1) for stable
 * numerical integration. Wave generators can be added to create dynamic wave sources.
 */
class world {
private:
    float speed;
	UpdateMethod method;

public:
    int rows, cols;
    uint32_t time_index = 0;

    /**
     * @brief Construct a new world object
     * @param r Number of rows in the simulation grid
     * @param c Number of columns in the simulation grid
     * @param s Wave propagation speed constant
	 * @param method Update method to use for simulation steps
     */
    world(int r, int c, float s, UpdateMethod method);
    

    /**
     * @brief Access value in the wave field at specified time and position
     * @param t Time offset: 0=current, 1=previous, 2=next time step
     * @param x X coordinate in the grid
     * @param y Y coordinate in the grid
     * @return Reference to the float value at the specified spacetime position
     */
    float& get(uint8_t t, int x, int y);

    /**
     * @brief Calculate the discrete Laplacian at specified position
     * @param t Time offset for the calculation
     * @param x X coordinate in the grid
     * @param y Y coordinate in the grid
     * @return The computed Laplacian value: nabla2(u) = u(x+1, y) + u(x-1, y) + u(x, y+1) + u(x, y-1) - 4*u(x, y)
     *
     * This implements the 5-point stencil discrete Laplacian used in the wave equation update.
     */
    float lap(uint8_t t, int x, int y);

    /**
     * @brief Advance simulation by one time step using the chosen method.
     */
    void update();

    /**
	 * @brief Calculate the next frame of simulation using compiler flag for parallelization.
     */
	void calculate_basic();

    /**
	* @brief Calculate the next frame of simulation using CUDA acceleration on the GPU.
	* MUST BE COMPILED WITH CUDA SUPPORT. NO WRAPPING SUPPORTED.
	* #TODO: Implement boundary wrapping for CUDA version.
    */
    void calculate_cuda();

    /**
     * @brief Add a wave generator to the simulation
     * @param generator - functor that modifies the wave field to create wave sources
     *
     * Generators are called each frame before the wave update and can inject energy into the field.
     */

    void add_generator(std::function<void(world&, int)> generator);
    std::array<std::vector<float>, 3> map;
    std::vector<std::function<void(world&, int)>> generators;
};
