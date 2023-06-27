//promise <--> future
#include <iostream>
#include <future>

using namespace std;

void add_func(promise<int> &mypromise, int x, int y);

int main(void)
{
	promise<int> pm;
	future<int> future;
	future = pm.get_future();  //make future<->prmoise get relationship

	thread t(add_func, ref(pm), 10, 20);

	int sum = future.get(); //wait for child thread calculate result, blocked function
	cout << "sum = " << sum << endl;

	t.join();

	return 0;
}

void add_func(promise<int> &mypromise, int x, int y)
{
	cout << "x = " << x << ", y = " << y << endl;
	int sum = 0;
	sum = x + y;
	this_thread::sleep_for(chrono::seconds(5));

	mypromise.set_value(sum);
}
