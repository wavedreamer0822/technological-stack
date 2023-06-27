#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

using namespace std;

void funct(void);

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
	funct();

	for(int i = 0; i < 100; ++i)
	{
		cout << "Main thread is running!" << endl;
		sleep(1);
	}

	cout << "Bye!" << endl;

	return 0;
}

void funct(void)
{
	int id = 1;
	int count = 10;
	string str = "Hello world";

	Show s1(id, count, str);
	thread t1(s1);

	int n1, n2;
	cout << "Please enter two numbers: " << endl;
	cin >> n1 >> n2;
	
	try
	{
		if(n2 == 0)
			throw runtime_error("n2 can't be 0");
		cout << "n1 / n2 = " << n1 / n2 << endl;
	}
	catch(runtime_error err)
	{
		cout << "Quit with exception" << endl;
		t1.join();
		return;
	}

	t1.join();
}
