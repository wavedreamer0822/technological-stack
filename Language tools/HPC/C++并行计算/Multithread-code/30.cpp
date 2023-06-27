//packaged_task <---> future
#include <iostream>
#include <future>

using namespace std;

int add_func(int x, int y);

int main(void)
{
	cout << "main() thread id = " << this_thread::get_id() << endl;

	packaged_task<int(int, int)> ptk(add_func);
	future<int> future;
	future = ptk.get_future();
	thread t(move(ptk), 10, 20);
	int result = future.get();
	cout << "Add result = " << result << endl;
	t.join();

	return 0;
}

int add_func(int x, int y)
{
	cout << "child thread id = " << this_thread::get_id() << endl;
	cout << "x = " << x << ", y = " << y << endl;
	return x + y;
}
