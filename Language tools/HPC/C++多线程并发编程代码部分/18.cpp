#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

void thread1(void);
void thread2(void);

mutex mt1;
mutex mt2;

int a = 100;
int b = 200;

int main(void)
{
	thread t1(thread1);
	thread t2(thread2);

	t1.join();
	t2.join();

	cout << "All threads end." << endl;
}

void thread1(void)
{
	cout << "Thread1 is running: " << endl;
	lock(mt1, mt2);
	lock_guard<mutex> guard1(mt1, adopt_lock);  //std::adopt_lock
	lock_guard<mutex> guard2(mt2, adopt_lock);
	cout << "Thread1: Shared data ---> a = " << a << endl;
	sleep(1);
	cout << "Thread1: Shared data ---> b = " << b << endl;
	cout << "Thread1: Get shared data: a + b = " << a + b << endl;
}

void thread2(void)
{
	cout << "Thread2 is running: " << endl;
	lock(mt1, mt2);
	lock_guard<mutex> guard1(mt1, adopt_lock);
	lock_guard<mutex> guard2(mt2, adopt_lock);
	cout << "Thread2: Shared data ---> b = " << b << endl;
	sleep(1);
	cout << "Thread2: Shared data ---> a = " << a << endl;
	cout << "Thread2: Get shared data: b - a = " << b - a << endl;
}
