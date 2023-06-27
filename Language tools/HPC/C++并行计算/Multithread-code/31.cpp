//packaged_task <---> future
#include <iostream>
#include <future>

using namespace std;

int main(void)
{
	cout << "main() thread id = " << this_thread::get_id() << endl;

	packaged_task<int(int, int)> ptk([](int x, int y){
		cout << "child thread id = " << this_thread::get_id() << endl;
		cout << "x = " << x << ", y = " << y << endl;
		return x + y;
	});
	future<int> future;
	future = ptk.get_future();
	thread t(move(ptk), 10, 20);
	int result = future.get();
	cout << "Add result = " << result << endl;
	t.join();

	return 0;
}

