#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

using namespace std;

class Show
{
	private:
		int id;
		int count;
		string str;
	public:
		Show(int i, int c, string s) : id(i), count(c), str(s){};
		void operator()() const
		{
			for(int i = 0; i < count; ++i)
			{
				cout << "Thread " << id << ": " << str << endl;
				sleep(1);
			}
		}
};

int main(void)
{
//	Show s1(1, 10, "Hello");
	Show s2(2, 20, "world");

//	thread t1(s1);
	thread t1(Show(1, 10, "Hello"));
	thread t2(s2);

	t1.join();
	t2.join();

	cout << "Bye!" << endl;

	return 0;
}

