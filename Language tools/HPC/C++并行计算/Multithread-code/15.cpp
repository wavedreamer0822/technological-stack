#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

class user_data
{
	public:
		int a;
		char c;

		void change_data(void){a *= 10; c += 10;}
};

user_data *unprotect_pt;

void function(user_data &my_data)
{
	unprotect_pt = &my_data;
}

class protect_data
{
	private:
		user_data data;   //protect shared data
		mutex guard_mutex;
	public:
		protect_data(){data.a = 1; data.c = 'A';}
		void process_data(void)
		{
			lock_guard<mutex> guard(guard_mutex);
			data.a += 10;
			data.c += 1;
			function(data);
			sleep(5);
		}
		void print(void)
		{
			cout << "data.a = " << data.a << ", data.c = " << data.c << endl;
		}
};

void thread_function(protect_data &pd)
{
	pd.process_data();
}

int main(void)
{
	protect_data pd;
	pd.print();

	thread t1(thread_function, ref(pd));
	thread t2(thread_function, ref(pd));

	t1.join();
	t2.join();

	pd.print();

	unprotect_pt->change_data();
	pd.print();

	return 0;
}

