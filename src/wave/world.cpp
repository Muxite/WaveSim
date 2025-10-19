#include "world.h"
#include "calculate_wave_cuda.h"


world::world(int c, int r, float s, UpdateMethod method) : rows(r), cols(c), speed(s), method(method) {
	for (auto i : { 0, 1, 2 })
	{
		// construct a ghost edge of 0s
		map[i] = std::vector<float>((rows + 2) * (cols + 2), 0);
	}
}

float& world::get(uint8_t t, int x, int y)
{	
	int stride = cols + 2;
	return map[(time_index + t) % 3][(y + 1) * stride + (x + 1)];
}

float world::lap(uint8_t t, int x, int y)
{
	return get(t, x + 1, y) + get(t, x - 1, y) + get(t, x, y + 1) + get(t, x, y - 1) - 4 * get(t, x, y);
}

void world::update()
{
	for (auto& generator : generators)
	{
		generator(*this, time_index);
	}

	switch (method)
	{
		case UpdateMethod::CUDA:
			calculate_cuda();
			break;
		default:
			calculate_basic();
			break;
	}


	time_index++;
}

void world::calculate_basic()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			get(2, x, y) = 2 * get(1, x, y) - get(0, x, y) + speed * speed * lap(1, x, y);
		}
	}
}

void world::calculate_cuda()
{
	calculate_wave_cuda_wrapper(
		map[time_index%3].data(),
		map[(time_index + 1)%3].data(),
		map[(time_index + 2)%3].data(),
		rows,
		cols,
		speed
	);
}

void world::add_generator(std::function<void(world&, int)> generator)
{
	generators.push_back(generator);
}

std::string update_method_to_string(UpdateMethod m) {
	switch (m) {
	case UpdateMethod::Basic: return "CPU (Automatic Parallization)";
	case UpdateMethod::CUDA: return "CUDA (GPU Compute)";
	default: return "Unknown";
	}
}