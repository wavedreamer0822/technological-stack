#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

using namespace std;

void show(int id, int count, const string &str);

int main(void)
{
	thread t1(show, 1, 10, "hello");
	thread t2(show, 2, 20, "world");

	t1.join();
	t2.join();

	cout << "Bye!" << endl;

	return 0;
}

void show(int id, int count, const string &str)
{
	for(int i = 0; i < count; ++i)
	{
		cout << "Thread " << id << ": " << str << endl;
		sleep(1);
	}
}
