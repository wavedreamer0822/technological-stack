#pragma once
#include <mutex>

namespace LxCFD
{
	class ComputeState
	{
	public:
		enum class ComputeStateTypes
		{
			NotRunning,
			Running,
			Running_InterruptByUser,
			Running_InterruptByError,
		};

	private:
		static ComputeStateTypes _ComputeState;
		static volatile bool _SettingChanged;
		static std::mutex _LocalMutex;

	public:
		static bool IsNeedInterrupt();
		static bool IsSettingChanged();
		static void ReportSettingChanged();
		static void ReportSettingNoticed();
		static bool GetIsRunning();
		static bool SetIsRunning(bool isRunning);
		static void ReportInterrupt_ByUser();
		static void ReportInterrupt_FindError();
	};
}