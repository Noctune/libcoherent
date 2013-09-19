#include <array>
#include <random>
#include <glm/glm.hpp>
#include <generative/generative.hpp>
#include "examples.hpp"
#include "TGAImage.hpp"

void generative::examples::fractal(generative::examples::TGAImage& image)
{	
	using namespace std::placeholders;
	
	const int seed = 42;
	const float frequency = 5.0f;
	const float lacunarity = 2.0f;
	const float persistence = 0.5f;
	
	std::minstd_rand prng(seed);
	generative::Permutation perm(prng);
	std::array<glm::vec2, 8> offsets;

	generative::offsets(offsets.begin(), offsets.end(), prng, 1000.0f);

	auto simplex = std::bind(generative::Simplex(), std::cref(perm), _1);

	auto begin = generative::make_offset_iterator(offsets.begin(), simplex),
		 end   = generative::make_offset_iterator(offsets.end(), simplex);
	
	for (int y = 0; y < image.height(); y++)
		for (int x = 0; x < image.width(); x++)
		{
			float rx = (float)x / image.width(), ry = (float)y / image.height();
			float value = generative::invert(generative::fractal_feedback(begin, end, lacunarity, persistence, glm::vec2(rx,ry) * frequency)) * 0xFF;
			image.set(x,y, value, value, value);
		}
}
