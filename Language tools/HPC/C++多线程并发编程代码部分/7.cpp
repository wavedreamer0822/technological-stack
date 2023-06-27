#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void threadFunction(int id);

int i = 0;
thread_local int j = 0;

int main(void)
{
	thread t1(threadFunction, 1);
	t1.join();

	thread t2(threadFunction, 2);
	t2.join();

	cout << "i = " << i << ", j = " << j << endl;

	return 0;
}

void threadFunction(int id)
{
	cout << "Thread " << id << ", i = " << i << ", j = " << j << endl;
	++i;
	++j;
}
