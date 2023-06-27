#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void show(int count, const string &str);

int main(void)
{
	thread t1(show, 10, "Hello");
	cout << "Thread1 id = " << t1.get_id() << endl;
	sleep(5);

	thread t2 = move(t1);
	cout << "Thread2 id = " << t2.get_id() << endl;

	cout << "t1.joinalbe = " << t1.joinable() << endl;
	cout << "t2.joinalbe = " << t2.joinable() << endl;
 
	if(t1.joinable())
		t1.join();
	if(t2.joinable())
		t2.join();
//	cout << "t2.joinalbe = " << t2.joinable() << endl;


	thread t3;
//	cout << "t3.joinable = " << t3.joinable() << endl;
	if(t3.joinable())
		t3.join();

	cout << "Bye!" << endl;

	return 0;
}

void show(int count, const string &str)
{
	for(int i = 0; i < count; i++)
	{
		cout << str << endl;
		sleep(1);
	}
}
