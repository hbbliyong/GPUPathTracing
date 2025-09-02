#include "iostream"
#include "glm/glm.hpp"
#include "thread_pool.hpp"
#include "film.hpp"
#include "camera.hpp"
#include "ray.hpp"
#include "sphere.hpp"
int main()
{
	ThreadPool thread_pool{};
	Film film(1280, 768);

	Sphere sphere{ {0,0,0}, 0.5f };

	glm::vec3 light_pos{ 1,1,1 };
	Camera camera(film, { 0,0,1 }, { 0,0,0 }, 90.0f);

	thread_pool.parallelFor(film.getWidth(), film.getHeight(), [&](size_t x, size_t y)
		{
			auto ray = camera.generateRay({ x,y });
			auto result = sphere.intersect(ray);
			if (result.has_value())
			{
				glm::vec3 hit_point = ray.hit(result.value());
				glm::vec3 normal = glm::normalize(hit_point - sphere.center);
				glm::vec3 light_dir = glm::normalize(light_pos - hit_point);
				float diff = glm::max(glm::dot(normal, light_dir), 0.0f);
				film.setPixel(x, y, { diff, diff, diff });
			}	
		});
	thread_pool.wait();
	film.save("test.ppm");

	std::cout << "Finished" << std::endl;

	return 0;
}