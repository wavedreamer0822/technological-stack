#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

mutex mtx;
condition_variable produce, consume;

int cargo = -1;

void consumer(void);
void producer(int n);

int main(void)
{
	thread consumers[10], producers[10];

	for(int i = 0; i < 10; i++)
	{
		consumers[i] = thread(consumer);
		producers[i] = thread(producer, i+1);
	}

	for(int i = 0; i < 10; i++)
	{
		consumers[i].join();
		producers[i].join();
	}

	return 0;
}

void consumer(void)
{
	unique_lock<mutex> lck(mtx);
	if(cargo == -1)
	{
		cout << "Consumer waits for cargo!" << endl;
		consume.wait(lck);
	}
	cout << cargo << endl;
	cargo = -1;
	produce.notify_one();
}

void producer(int n)
{
	sleep(5);
	unique_lock<mutex> lck(mtx);
	if(cargo != -1)
		produce.wait(lck);
	cargo = n;
	consume.notify_one();
}
