#include "iostream"
#include "glm/glm.hpp"
#include "thread_pool.hpp"
#include "film.hpp"
class SimpleTask : public Task
{
public:
	void run() override
	{
		std::cout << "hello world!" << std::endl;
	}
};

int main()
{
	ThreadPool thread_pool{};
	Film film(1280, 768);
	thread_pool.parallelFor(200, 100, [&](size_t x, size_t y)
		{
			film.setPixel(x, y, { 0.5, 0.7, 0.2 });
		});
	thread_pool.wait();
	film.save("test.ppm");
	glm::vec3 test = { 1, 2, 3 };
	std::cout << "hello world" << test.x << test.y << test.z << std::endl;

	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	return 0;
}