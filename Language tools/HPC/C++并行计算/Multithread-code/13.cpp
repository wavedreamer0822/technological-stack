#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

using namespace std;

int parallel_accumulate(vector<int>::iterator first, vector<int>::iterator last, int init);
void accumulate_block(vector<int>::iterator first, vector<int>::iterator last, int &sum);

int main(void)
{
	vector<int> ivec(100);

	for(int i = 1; i <= 100; ++i)
		ivec.push_back(i);

	cout << parallel_accumulate(ivec.begin(), ivec.end(), 0) << endl;

	return 0;
}

int parallel_accumulate(vector<int>::iterator first, vector<int>::iterator last, int init)
{
	const unsigned int length = distance(first, last);
	if(!length)
		return init;
	const unsigned int min_per_thread = 25;
	const unsigned int max_threads = (length + min_per_thread - 1) / min_per_thread;
	const unsigned int hardware_threads = thread::hardware_concurrency();
	const unsigned int num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	const unsigned int block_size = length / num_threads;

	vector<thread> threads(num_threads - 1);
	vector<int> results(num_threads);

	vector<int>::iterator block_start = first;
	for(int i = 0; i < (num_threads-1); ++i)
	{
		vector<int>::iterator block_end = block_start;
		advance(block_end, block_size);
		threads[i] = thread(accumulate_block, block_start, block_end, ref(results[i]));   //accumulate(, , );
		block_start = block_end;
	}
	accumulate_block(block_start, last, results[num_threads-1]);

	for(auto &r : threads)
		r.join();

	return accumulate(results.begin(), results.end(), init);
}

void accumulate_block(vector<int>::iterator first, vector<int>::iterator last, int &sum)
{
	sum = accumulate(first, last, sum);
}
