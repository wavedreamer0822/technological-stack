#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

mutex mtx;
condition_variable flag;
int count = -1;

void signal();
void wait(int id);

int main(void)
{
	thread t1(signal);
	thread t2(wait, 2);
	thread t3(wait, 3);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}

void signal(void)
{
	sleep(5);
	unique_lock<mutex> lck(mtx);
	cout << "notify all threads" << endl;
	lck.unlock();
	flag.notify_all();

	sleep(5);
	lck.lock();
	count = 1;
	cout << "notify all threads again" << endl;
	lck.unlock();
	flag.notify_all();
}

void wait(int id)
{
	unique_lock<mutex> lck(mtx);
	cout << "Thread " << id << " waits for count: " << endl;
	flag.wait(lck, [](){return count == 1;});
	cout << "Thread " << id << ": " << count << endl;
	//sleep(1); 
}
