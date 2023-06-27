#include <iostream>
#include <future>
#include <unistd.h>

using namespace std;

bool is_prime(int x);

//async(1) launch::async   2) launch::deferred)
int main(void)
{
//	future<bool> fut = async(launch::async, is_prime, 313222313);
//	future<bool> fut = async(is_prime, 313222313);
//	future<bool> fut = async(launch::deferred, is_prime, 313222313);	
	future<bool> fut = async(launch::async|launch::deferred, is_prime, 313222313);	

	cout << "Checking whether 313222313 is prime." << endl;
	cout << "main() thread id = " << this_thread::get_id() << endl;
	sleep(5);

	bool ret = fut.get();

	if(ret)
		cout << "It is prime" << endl;
	else
		cout << "It is not prime" << endl;
}

bool is_prime(int x)
{
	cout << "Calculating. Please wait....." << endl;
	cout << "is_primer() thread id = " << this_thread::get_id() << endl;
	sleep(5);

	for(int i = 2; i < x; i++)
	{
		if(x % i == 0)
			return false;
	}
	return true;
}
