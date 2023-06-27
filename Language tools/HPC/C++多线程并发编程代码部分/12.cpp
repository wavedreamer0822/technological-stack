#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

using namespace std;

void show(int id, int count, const string &str);

int main(void)
{
	cout << thread::hardware_concurrency() << endl;

	thread t1(show, 1, 100, "hello");
	thread t2(show, 2, 100, "world"); 
	thread t3(show, 3, 100, "good");
	thread t4(show, 4, 100, "morning"); 

	t1.join();
	t2.join();
	t3.join();
	t4.join();

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
