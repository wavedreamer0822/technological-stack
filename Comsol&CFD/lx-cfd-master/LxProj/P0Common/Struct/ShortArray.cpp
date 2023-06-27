#include "ShortArray.h"
#include <cstdio>
#include <iostream>
#include <ostream>

using namespace std;

namespace LxCFD
{
	ShortArray::Shallow::Shallow()
	{
	}
	ShortArray::Shallow::Shallow(int length, int *array)
	{
		_Length = length;
		_Array = array;
	}
	void ShortArray::Shallow::Reverse()
	{
		for (int start = 0, end = _Length - 1; start < end; ++start, --end)
		{
			int temp = _Array[start];
			_Array[start] = _Array[end];
			_Array[end] = temp;
		}
	}
	ShortArray::Shallow ShortArray::Deep::Create(int length)
	{
		return Shallow(length, RequireStorage(length));
	}
	ShortArray::Shallow ShortArray::Deep::Create(const std::vector<int> &vector)
	{
		Shallow sa = Create(vector.size());
		for (int i = 0; i < sa.GetLengh(); ++i)
		{
			sa[i] = vector[i];
		}
		return sa;
	}
	ShortArray::Shallow ShortArray::Deep::Create(const Shallow &array)
	{
		Shallow sa = Create(array.GetLengh());
		for (int i = 0; i < sa.GetLengh(); ++i)
		{
			sa[i] = array[i];
		}
		return sa;
	}
	ShortArray::Shallow ShortArray::Deep::Create( LinkArray<int>::List &list)
	{
		Shallow sa = Create(list.Length);
		int i = 0;
		for (auto &l : list)
		{
			sa.at(i) = l;
			++i;
		}
		return sa;
	}
	void ShortArray::Deep::Initialize(int listCapacity, int vectorCapacity)
	{
		_VectorCapacity = vectorCapacity;
		_StorageList.reserve(listCapacity);
		if (_StorageList.size() == 0)
		{
			_StorageList.push_back(std::unique_ptr<std::vector<int>>(new std::vector<int>()));
			_StorageList.back()->reserve(_VectorCapacity);
		}
	}
	std::string ShortArray::Deep::ToString()
	{
		std::stringstream ss;
		ss << "ShortArray:" << std::endl;
		int i = 0;
		for (auto &v : _StorageList)
		{
			ss << "vector " << i << ":";
			++i;
			for (auto &vi : *v)
			{
				ss << vi;
			}
			ss << std::endl;
		}
		return ss.str();
	}
	int *ShortArray::Deep::RequireStorage(int length)
	{
		if (length == 0)
		{
			return nullptr;
		}
		else if (length > _VectorCapacity)
		{
			throw std::invalid_argument("无法分配该长度");
		}
		if (_StorageList.size() == 0)
		{
			throw std::invalid_argument("未初始化");
		}
		{
			std::vector<int> &lastV1 = *_StorageList.back();
			if (lastV1.size() + length > lastV1.capacity())
			{
				_StorageList.push_back(std::unique_ptr<std::vector<int>>(new std::vector<int>()));
				_StorageList.back()->reserve(_VectorCapacity);
			}
		}
		{
			std::vector<int> &lastV2 = *_StorageList.back();
			lastV2.resize(lastV2.size() + length);
			return &lastV2[lastV2.size() - length];
		}
	}
}