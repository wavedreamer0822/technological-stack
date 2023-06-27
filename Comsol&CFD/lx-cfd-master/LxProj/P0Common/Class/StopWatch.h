#pragma once
#include <iostream>
#include <time.h>
class StopWatch
{
public:
	void Start()
	{
		_StartTime = clock();
	}
	double EndAndGet()
	{
		return (double)(clock() - _StartTime) / CLOCKS_PER_SEC;
	}

	void EndAndPrint()
	{
		std::cout << "The timespan is:" << EndAndGet() << "s" << std::endl;
	}

private:
	clock_t _StartTime;
};