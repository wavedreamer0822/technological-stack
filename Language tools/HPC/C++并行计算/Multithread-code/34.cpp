#include <iostream>
#include <mutex>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

timed_mutex tmx;

void fun1(int id, const string &str)
{
	if(tmx.try_lock())
	{
		cout << "Thread " << id << "locked and do something" << endl;
		//do something
		for(int i = 0; i < 10; i++)
		{
			cout << str << endl;
			this_thread::sleep_for(chrono::seconds(1));
		}
		tmx.unlock();
	}
}

void fun2(int id, const string &str)
{
	this_thread::sleep_for(chrono::seconds(1));

	if(tmx.try_lock_for(chrono::seconds(5)))
	{
		cout << "Thread " << id << ": " << str << endl;
		tmx.unlock();
	}
	else
		cout << "Can not wait any more" << endl;
}

int main(void)
{
	thread t1(fun1, 1, "Hello world");
	thread t2(fun2, 2, "Good morning");

	t1.join();
	t2.join();

	return 0;
}
