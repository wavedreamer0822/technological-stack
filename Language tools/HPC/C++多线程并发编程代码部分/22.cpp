#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

mutex mtx;
condition_variable flag;

int count = -1;

void thread1(void);
void thread2(void);
void thread3(void);

int main(void)
{
	thread t1(thread1);
	thread t2(thread2);
	thread t3(thread3);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}

void thread1(void)
{
	int i = 0;
	sleep(5);

	while(1)
	{
/*
		{
			lock_guard<mutex> lck(mtx);
			count = i++;
		}
*/
		unique_lock<mutex> lck(mtx);
		count = i++;
		lck.unlock();

		//flag.notify_one();
		flag.notify_all();
		sleep(1);
	}
}

void thread2(void)
{
	while(1)
	{
		unique_lock<mutex> lck(mtx);
		cout << "Thread2 waits for count: " << endl;
		flag.wait(lck);
		cout << count << endl;
	}
}

void thread3(void)
{
	while(1)
	{
		unique_lock<mutex> lck(mtx);
		cout << "Thread3 waits for count: " << endl;
		flag.wait(lck);
		cout << count << endl;
	}
}
