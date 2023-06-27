#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
namespace LxCFD
{
	class LxTool
	{
	public:
		static const double OneThird;
		static const double TwoThird;
		static double RoundOff(double x, int bit);
		template <typename T>
		inline static T Pow2(T x) { return x * x; }
		static std::string GetCurrentTime();
		template <typename T>
		static void CheckCreateVector(std::unique_ptr<std::vector<T>> &vector, std::size_t size)
		{
			if (vector == nullptr || vector->size() != size)
			{
				vector = std::unique_ptr<std::vector<T>>(new std::vector<T>(size));
			}
		}
		template <typename T>
		static void CheckCreateVector(std::shared_ptr<std::vector<T>> &vector, std::size_t size)
		{
			if (vector == nullptr || vector->size() != size)
			{
				vector = std::shared_ptr<std::vector<T>>(new std::vector<T>(size));
			}
		}

		static inline std::domain_error GetNotImplementedException()
		{
			return std::domain_error("Not implemented exception");
		}
	};
}