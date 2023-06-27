#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

mutex mt;

void thread1(int id, const string &str);

int main(void)
{
	thread t1(thread1, 1, "Hello world");
	t1.join();

	return 0;
}

/*
void thread1(int id, const string &str)
{
	lock_guard<mutex> guard(mt);
	cout << "Thread" << id << ": " << str << endl;
}
*/

void thread1(int id, const string &str)
{
	unique_lock<mutex> guard(mt, defer_lock);
	/*
		do_something()
	*/
	guard.lock();
	cout << "Thread" << id << ": " << str << endl;
	guard.unlock();

	int sum = 0;
	for(int i = 1; i <= 100; i++)
		sum += i;

	guard.lock();
	cout << "Thread" << id << ": " << sum << endl;
}
