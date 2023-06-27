#pragma once
#include <mutex>
#include <functional>
#include <condition_variable>
#include "ComputeState.h"
#include "LxConsole.h"

namespace LxCFD
{
	class MultiThreads
	{
	public:
		static std::mutex GlobalMutex;
		static void RunHostTask(const std::function<void(void)> &hostTask);
		static void RunCalTasks(const std::function<void(int)> &calTask);
		static inline int GetThreadsCount() { return _ThreadsCount; }
		static void SetThreadsCout(int threadsCout);
		static void Sync(int taskIndex);
		static void Sync(int taskIndex, const std::function<void(void)> &runOnce);

	private:
		static volatile bool _IsContinue;
		static volatile int _ThreadsCount;
		static volatile int _FinishedCount;
		static std::mutex _LocalMutex;
		static std::condition_variable _HostTaskCondition;
		static std::condition_variable _CalTaskCondition;
		static std::function<void(int)> _CalTask;
		static void totalHostTask(const std::function<void(void)> &hostTask);
		static void totalCalTask(int taskIndex);
		static bool isLastTask();
	};
}