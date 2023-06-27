#include <iostream>
#include <thread>

using namespace std;

void threadFunction(int n);

int main(void)
{
	int i = 0;

	thread t1(threadFunction, i);
	t1.join();

	cout << "i = " << i << endl;

	return 0;
}

void threadFunction(int n)
{
	n += 100;
}
