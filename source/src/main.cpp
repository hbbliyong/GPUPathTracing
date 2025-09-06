#include "iostream"
#include "glm/glm.hpp"
#include "thread_pool.hpp"
#include "film.hpp"
#include "camera.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include <atomic>
int main()
{
	ThreadPool thread_pool{};
	Film film(1280, 768);

	Sphere sphere{{0, -0.5, 0}, 0.5f};
	Sphere sphere1{{0, 0.5, 0}, 0.5f};
	glm::vec3 light_pos{1, 1, 1};
	Camera camera(film, {0, 0, 1}, {0, 0, 0}, 90.0f);

	std::atomic<int> pixel_count{0};
	int sumPixels = film.getWidth() * film.getHeight();
	auto computer = [&](Ray &ray, Sphere &sphere, Film &film, glm::vec3 &light_pos, size_t x, size_t y)
	{
		Shape& shape = sphere;

		auto hit_info = shape.intersect(ray,0.001f,100.0f);
		if (hit_info.has_value())
		{
			glm::vec3 hit_point = ray.hit(result.value());
			glm::vec3 normal = glm::normalize(hit_point - sphere.center);
			glm::vec3 light_dir = glm::normalize(light_pos - hit_point);
			float diff = glm::max(glm::dot(normal, light_dir), 0.0f);
			film.setPixel(x, y, {diff, diff, diff});
		}
	};
	thread_pool.parallelFor(film.getWidth(), film.getHeight(), [&](size_t x, size_t y)
							{
			auto ray = camera.generateRay({ x,y });
			computer(ray,sphere,film,light_pos,x,y);
			// computer(ray,sphere1,film,light_pos,x,y);
			pixel_count++;
			if (pixel_count % film.getWidth() == 0)
			{
				std::cout << "Rendered " << static_cast<float>(pixel_count)/sumPixels << " pixels\r" << std::flush;
			} });

	thread_pool.wait();
	film.save("test.ppm");

	// std::cout << "Finished" << std::endl;

	return 0;
}