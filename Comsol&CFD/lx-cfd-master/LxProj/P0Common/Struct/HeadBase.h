#pragma once
#include <string>

namespace LxCFD
{
	class HeadBase
	{
	public:
		virtual ~HeadBase() = default;
		std::string Name;
		int ID = -1;
	};
}