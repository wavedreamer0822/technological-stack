#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void do_something(void)
{
	this_thread::sleep_for(chrono::duration<int, ratio<1, 1>>(2));//chrono::duration<int, ration<60, 1>>, chrono::duration<double, <1, 1000>>  1/1000
	cout << "do something" << endl;
}

int main(void)
{
	auto start = chrono::high_resolution_clock::now();
	do_something();
	auto stop = chrono::high_resolution_clock::now();

	auto durations = chrono::duration<double, ratio<1, 1>>(stop - start).count();

	cout << "do_something takes " << durations << " seconds." << endl;

	return 0;
}
