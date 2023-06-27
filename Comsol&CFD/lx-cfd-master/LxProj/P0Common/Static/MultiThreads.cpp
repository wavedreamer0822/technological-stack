#include <thread>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <sstream>
#include "MultiThreads.h"

namespace LxCFD
{
	//public
	std::mutex MultiThreads::GlobalMutex;
	//private
	volatile bool MultiThreads::_IsContinue = false;
	volatile int MultiThreads::_ThreadsCount = 1;
	volatile int MultiThreads::_FinishedCount = 0;
	std::mutex MultiThreads::_LocalMutex;
	std::condition_variable MultiThreads::_HostTaskCondition;
	std::condition_variable MultiThreads::_CalTaskCondition;
	std::function<void(int)> MultiThreads::_CalTask;
	void MultiThreads::SetThreadsCout(int threadsCount)
	{
		if (ComputeState::GetIsRunning())
		{
			LxConsole::Warn("正在计算中，不可更改线程数");
		}
		if (threadsCount <= 0)
		{
			LxConsole::Warn("线程数不可设置小于1,已更正为1");
			_ThreadsCount = 1;
		}
		else
		{
			_ThreadsCount = threadsCount;
		}
	}
	void MultiThreads::totalHostTask(const std::function<void(void)> &hostTask)
	{
		_IsContinue = true;
		_FinishedCount = 0;
		_CalTask = [](int a) {};
		std::vector<std::thread> tasks(_ThreadsCount);
		{
			std::unique_lock<std::mutex> lock(_LocalMutex);
			for (int i1 = 0; i1 < _ThreadsCount; ++i1)
			{
				int k = i1;
				tasks[i1] = std::thread(totalCalTask, k);
			}
			_HostTaskCondition.wait(lock);
		}
		_CalTask = nullptr;
		try
		{
			hostTask();
		}
		catch (const std::exception &e)
		{
			if (_IsContinue)
			{
				std::stringstream ss;
				ss << "主计算线程出现错误：" << e.what();
				LxConsole::Error(ss.str());
				LxConsole::Error("所有计算线程已退出");
			}
		}
		_IsContinue = false;
		_CalTask = nullptr;
		_CalTaskCondition.notify_all();
		for (int i1 = 0; i1 < _ThreadsCount; ++i1)
		{
			tasks[i1].join();
		}
		ComputeState::SetIsRunning(false);
	}
	void MultiThreads::RunHostTask(const std::function<void(void)> &hostTask)
	{
		if (!ComputeState::SetIsRunning(true))
		{
			LxConsole::Warn(std::string("正在运行中"));
			return;
		}
		std::thread host = std::thread(totalHostTask, hostTask);
		host.detach();
	}
	void MultiThreads::totalCalTask(int taskIndex)
	{
		try
		{
			do
			{
				_CalTask(taskIndex);
				std::unique_lock<std::mutex> lock(_LocalMutex);
				if (isLastTask())
				{
					_HostTaskCondition.notify_one();
				}
				_CalTaskCondition.wait(lock);
			} while (_IsContinue);
		}
		catch (const std::exception &e)
		{
			std::unique_lock<std::mutex> lock(_LocalMutex);
			if (_IsContinue) //第一次报错
			{
				_IsContinue = false;
				std::stringstream ss;
				ss << "计算线程" << taskIndex << "出现错误：" << e.what();
				LxConsole::Error(ss.str());
				_HostTaskCondition.notify_one();
			}
		}
	}
	void MultiThreads::RunCalTasks(const std::function<void(int)> &calTask)
	{
		if (_CalTask != nullptr)
			throw std::domain_error("子线程不可继续开启子线程");
		_CalTask = calTask;
		{
			std::unique_lock<std::mutex> lock(_LocalMutex);
			_CalTaskCondition.notify_all();
			_HostTaskCondition.wait(lock);
		}
		_CalTask = nullptr;
		if (!_IsContinue)
			throw std::domain_error("20210810");
	}

	void MultiThreads::Sync(int taskIndex)
	{
		Sync(taskIndex, [] {});
	}
	void MultiThreads::Sync(int taskIndex, const std::function<void(void)> &runOnce)
	{
		std::unique_lock<std::mutex> lock(_LocalMutex);
		if (isLastTask())
		{
			runOnce();
			_CalTaskCondition.notify_all();
		}
		else
		{
			_CalTaskCondition.wait(lock);
		}
		if (!_IsContinue)
			throw std::domain_error("20210810");
	}
	bool MultiThreads::isLastTask()
	{
		if (!_IsContinue)
			throw std::domain_error("20210810");
		++_FinishedCount;
		if (_FinishedCount == _ThreadsCount)
		{
			_FinishedCount = 0;
			return true;
		}
		return false;
	}
}