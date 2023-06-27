#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <memory>

namespace LxCFD
{
	class LxConsole
	{
	public:
		 class IConsole
		 {
		 public:
		 	virtual void Calc(const std::string &stringMessage) = 0;
		 	virtual void Info(const std::string &stringMessage) = 0;
		 	virtual void Warn(const std::string &stringMessage) = 0;
		 	virtual void Error(const std::string &stringMessage) = 0;
		 };

		 class DefaultConsole : public IConsole
		 {
		 public:
		 	virtual void Calc(const std::string &stringMessage) override;
		 	virtual void Info(const std::string &stringMessage) override;
		 	virtual void Warn(const std::string &stringMessage) override;
		 	virtual void Error(const std::string &stringMessage) override;

		 protected:
		 	std::mutex ConsoleMutex;
		 };

	private:
		static std::unique_ptr<IConsole> _LxConsole;

	public:
		static void SetConsole(std::unique_ptr<IConsole> newConsole);
		static void Calc(const std::string &stringMessage);
		static void Info(const std::string &stringMessage);
		static void Warn(const std::string &stringMessage);
		static void Error(const std::string &stringMessage);
	};

}
