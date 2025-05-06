#include "iostream"
#include "glm/glm.hpp"
#include "thread_pool.hpp"
class SimpleTask :public Task
{
public:
	void run()override
	{
		std::cout << "hello world!" << std::endl;
	}
};

int main()
{
	glm::vec3 test = { 1,2,3 };
	std::cout << "hello world" << test.x << test.y << test.z << std::endl;
	ThreadPool thread_pool{};
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	thread_pool.addTask(new SimpleTask());
	return 0;
}