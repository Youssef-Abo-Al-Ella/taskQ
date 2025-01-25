#include<iostream>

#include "../Task.h"
int main()
{
	Task test("test");
	std::cout << test.getFormatedDate();
	test.wirteToDisk();
	std::vector<Task> testvector= test.readFromDisk();

	std::cin.get();
}