#include <iostream>
#include <thread>

using namespace std;

void threadFunction(int &r);

int main(void)
{
	int i = 0;

	thread t1(threadFunction, ref(i));  //std::ref()
	t1.join();

	cout << "i = " << i << endl;

	return 0;
}

void threadFunction(int &r)
{
	r += 100;
}
