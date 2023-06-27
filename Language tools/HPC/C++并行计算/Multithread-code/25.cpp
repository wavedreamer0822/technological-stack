#include <iostream>
#include <future>
#include <unistd.h>

using namespace std;

bool is_prime(int x);

int main(void)
{
	future<bool> fut = async(is_prime, 313222313);
	cout << "Checking whether 313222313 is prime." << endl;

	bool ret = fut.get();

	if(ret)
		cout << "It is prime" << endl;
	else
		cout << "It is not prime" << endl;
}

bool is_prime(int x)
{
	cout << "Calculating. Please wait....." << endl;
	sleep(5);

	for(int i = 2; i < x; i++)
	{
		if(x % i == 0)
			return false;
	}
	return true;
}
