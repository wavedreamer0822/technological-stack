#include <iostream>
#include <future>

using namespace std;

void thread1(promise<int> &mypromise, int n);
void thread2(future<int> &fut);

int main(void)
{
	promise<int> pm;
	future<int> future;
	future = pm.get_future();

	thread t1(thread1, ref(pm), 5);
	thread t2(thread2, ref(future));

	t1.join();
	t2.join();

	return 0;
}

void thread1(promise<int> &mypromise, int n)
{
	cout << "thread1 input value: " << n << endl;
	n *= 100;
	this_thread::sleep_for(chrono::seconds(5));
	mypromise.set_value(n);
}

void thread2(future<int> &fut)
{
	cout << "thread2 get vaule: " << fut.get() << endl;
}
