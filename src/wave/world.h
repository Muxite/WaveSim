#pragma once
#include <vector>
#include <functional>
#include <array>

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

public:
    int rows, cols;
    uint32_t time_index = 0;

    /**
     * @brief Construct a new world object
     * @param r Number of rows in the simulation grid
     * @param c Number of columns in the simulation grid
     * @param s Wave propagation speed constant
     * @param wrap If true, simulates toroidal wrapping at edges; if false, uses fixed boundaries
     */
    world(int r, int c, float s, bool wrap);
    bool wrap;

    /**
     * @brief Access value in the wave field at specified time and position
     * @param t Time offset: 0=current, 1=previous, 2=next time step
     * @param x X coordinate in the grid
     * @param y Y coordinate in the grid
     * @return Reference to the float value at the specified spacetime position
     *
     * Handles boundary conditions automatically based on wrap flag. Returns a dummy
     * reference for out-of-bounds access when not wrapping.
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
     * @brief Advance simulation by one time step using single-threaded computation
     */
    void update();

    /**
	 * @brief Advance simulation by one time step. Uses compiler flag for parallelization.
     */
	void update_parallel();

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
