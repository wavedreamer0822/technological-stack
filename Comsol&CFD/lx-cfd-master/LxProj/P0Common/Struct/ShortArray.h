#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <exception>
#include "LinkArray.h"
namespace LxCFD
{
	class ShortArray
	{
	public:
		struct Shallow
		{
		public:
			Shallow();
			Shallow(int length, int *array);
			void Reverse();
			inline int GetLengh() const { return _Length; }
			inline int *GetArray() const { return _Array; }
			inline int &operator[](int index) const { return this->_Array[index]; }
			inline int &at(int index) const
			{
				if (index < 0 || index >= _Length)
					throw std::out_of_range("out of range!");
				return this->_Array[index];
			}
			inline int *begin() const { return _Array; }
			inline int *end() const { return _Array + _Length; }

		private:
			int _Length = 0;
			int *_Array = nullptr;
		};
		class Deep
		{
		public:
			Shallow Create(int length);
			Shallow Create(const std::vector<int> &vector);
			Shallow Create(const Shallow &shallowtArray);
			Shallow Create(LinkArray<int>::List &list);
			void Initialize(int listCapacity, int vectorCapacity);
			std::string ToString();

		protected:
			std::vector<std::unique_ptr<std::vector<int>>> _StorageList;
			int _VectorCapacity = 4096;
			int *RequireStorage(int length);
		};
	};
}
