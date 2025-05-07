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
	Film film(1280, 768);
	for (size_t i = 0; i < 200; i++)
	{
		for (size_t j = 0; j < 200; j++)
		{
			film.ssetPixel(i, j, {0.1, 0.2, 0.3});
		}
	}
	film.save("test.ppm");
	glm::vec3 test = {1, 2, 3};
	std::cout << "hello world" << test.x << test.y << test.z << std::endl;
	ThreadPool thread_pool{};
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	return 0;
}