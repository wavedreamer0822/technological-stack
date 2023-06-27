#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void hello(void);

int main(void)
{
	thread t1(hello);

	t1.join();

	cout << "Bye!" << endl;

	return 0;
}

void hello(void)
{
	for(int i = 0; i < 10; ++i)
	{
		cout << "Hello world!" << endl;
		sleep(1);
	}
}
