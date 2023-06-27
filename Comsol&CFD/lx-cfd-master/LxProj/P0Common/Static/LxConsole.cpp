#include "LxConsole.h"
#include "LxTool.h"
namespace LxCFD
{
	std::unique_ptr<LxConsole::IConsole> LxConsole::_LxConsole = std::unique_ptr<LxConsole::DefaultConsole>(new LxConsole::DefaultConsole());
	void LxConsole::SetConsole(std::unique_ptr<IConsole> newConsole)
	{
		if (newConsole != nullptr)
		{
			_LxConsole = std::move(newConsole);
		}
	}
	void LxConsole::DefaultConsole::Calc(const std::string &stringMessage)
	{
		std::unique_lock<std::mutex> lock(ConsoleMutex);
		std::cout << stringMessage << std::endl;
	}
	void LxConsole::DefaultConsole::Info(const std::string &stringMessage)
	{
		std::unique_lock<std::mutex> lock(ConsoleMutex);
		std::cout << LxTool::GetCurrentTime() << "  " << stringMessage << std::endl;
	}
	void LxConsole::DefaultConsole::Warn(const std::string &stringMessage)
	{
		std::unique_lock<std::mutex> lock(ConsoleMutex);
		std::cout << LxTool::GetCurrentTime() << "  " << stringMessage << std::endl;
	}
	void LxConsole::DefaultConsole::Error(const std::string &stringMessage)
	{
		std::unique_lock<std::mutex> lock(ConsoleMutex);
		std::cout << LxTool::GetCurrentTime() << "  " << stringMessage << std::endl;
	}
	void LxConsole::Calc(const std::string &stringMessage)
	{
		_LxConsole->Calc(stringMessage);
		//std::cout << stringMessage << std::endl;
	}
	void LxConsole::Info(const std::string &stringMessage)
	{
		_LxConsole->Info(stringMessage);
		//std::cout << LxTool::GetCurrentTime() << "  " << stringMessage << std::endl;
	}
	void LxConsole::Warn(const std::string &stringMessage)
	{
		_LxConsole->Warn(stringMessage);
		//std::cout << LxTool::GetCurrentTime() << "  " << stringMessage << std::endl;
	}
	void LxConsole::Error(const std::string &stringMessage)
	{
		_LxConsole->Error(stringMessage);
		//std::cout << LxTool::GetCurrentTime() << "  " << stringMessage << std::endl;
	}

}
