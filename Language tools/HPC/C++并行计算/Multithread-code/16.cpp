#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

void thread1(void);
void thread2(void);

mutex mt;
int num = 100;

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
	lock_guard<mutex> guard(mt);
	cout << "Thread1: Shared data ---> num = " << num << endl;
	while(1);
}

void thread2(void)
{
	cout << "Thread2 is running: " << endl;
	sleep(1);  //this_thread::sleep_for(chrono::seconds(1));
	lock_guard<mutex> guard(mt);
	cout << "Thread2: Shared data ---> num = " << num << endl;
}
