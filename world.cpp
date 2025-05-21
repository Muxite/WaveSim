#include "world.h"


world::world(int c, int r, float s, bool wrap) : rows(r), cols(c), speed(s), wrap(wrap) {
	for (auto i : { 0, 1, 2 })
	{
		map[i] = std::vector<float>(rows * cols, 0);
	}
}

float& world::get(uint8_t t, int x, int y)
{	
	static float dummy = 0.f;
	if (wrap)
	{
		y = (y % rows + rows) % rows;
		x = (x % cols + cols) % cols;
	}
	if (x < 0 || x >= cols || y < 0 || y >= rows)
	{
		return dummy;
	}
	return map[(time_index + t) % 3][y * cols + x];
}

float world::lap(uint8_t t, int x, int y)
{
	return get(t, x + 1, y) + get(t, x - 1, y) + get(t, x, y + 1) + get(t, x, y - 1) - 4 * get(t, x, y);
}

void world::update()
{
	for (auto& generator : generators)
	{
		// call functor of generator object.
		generator(*this, time_index);
	}

	#pragma omp parallel for collapse(2)
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			get(2, x, y) = 2 * get(1, x, y) - get(0, x, y) + speed * speed * lap(1, x, y);
		}
	}


	time_index++;
}

void world::add_generator(std::function<void(world&, int)> generator)
{
	generators.push_back(generator);
}

