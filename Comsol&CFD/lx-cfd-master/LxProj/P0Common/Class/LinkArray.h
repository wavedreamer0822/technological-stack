#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
namespace LxCFD
{
	template <typename T>
	class LinkArray
	{
	public:
		struct Node
		{
		public:
			Node(T tValue) : Value(tValue) {}
			T Value;
			Node* Next = nullptr;
		};

		struct Iterator
		{
		public:
			Iterator(Node* node) : _Node(node) {}
			bool operator!=(const LinkArray<T>::Iterator& other) const
			{
				return _Node != other._Node;
			}
			T& operator*()
			{
				return _Node->Value;
			}
			Node& operator++()
			{
				_Node = _Node->Next;
				return *_Node;
			}

		private:
			Node* _Node;
		};
		struct List
		{
		public:
			int Length = 0;
			Node* First = nullptr;
			Node* Last = nullptr;

			void Clear()
			{
				Length = 0;
				First = nullptr;
				Last = nullptr;
			}
			Iterator begin()
			{
				return Iterator(First);
			}
			Iterator end()
			{
				return Iterator(nullptr);
			}
			void AppendMoveRange(List& appendent)
			{
				if (Length == 0)
				{
					First = appendent.First;
				}
				else
				{
					Last->Next = appendent.First;
				}
				Last = appendent.Last;
				Length += appendent.Length;
				appendent.Clear();
			}

			std::string ToString()
			{
				std::stringstream ss;
				ss << "LinkArray::List :";
				for (auto& l : *this)
				{
					ss << " " << l;
				}
				ss << std::endl;
				return ss.str();
			}
		};
		class Deep
		{
		public:
			void Initialize(int listCapacity, int maxVectorCapacity)
			{
				if (_VectorCapacity < maxVectorCapacity)
				{
					_VectorCapacity = maxVectorCapacity;
					_StorageList.clear();
					_WorkingVector = -1;
				}
				if (_WorkingVector < 0)
				{
					_StorageList.push_back(std::unique_ptr<std::vector<Node>>(new std::vector<Node>()));
					_StorageList.back()->reserve(_VectorCapacity);
				}
				else
				{
					for (; _WorkingVector >= 0; --_WorkingVector)
					{
						_StorageList.at(_WorkingVector)->clear();
					}
				}
				_WorkingVector = 0;
				_StorageList.reserve(listCapacity);
			}

			void CreateAdd(List& targetList, const T& value)
			{
				std::vector<Node>& lastV1 = *_StorageList.at(_WorkingVector);
				if (lastV1.size() >= lastV1.capacity())
				{
					++_WorkingVector;
					if (_WorkingVector >= (int)_StorageList.size())
					{
						_StorageList.push_back(std::unique_ptr<std::vector<Node>>(new std::vector<Node>()));
						_StorageList.back()->reserve(_VectorCapacity);
					}
				}
				std::vector<Node>& lastV2 = *_StorageList.at(_WorkingVector);
				lastV2.push_back(Node(value));
				Node* lastNode = &lastV2.back();
				if (targetList.Length == 0)
				{
					targetList.First = lastNode;
				}
				else
				{
					targetList.Last->Next = lastNode;
				}
				targetList.Last = lastNode;
				++targetList.Length;
			}
			std::string ToString()
			{
				std::stringstream ss;
				ss << "LinkArray::Deep :" << std::endl;
				int i = 0;
				for (auto& v : _StorageList)
				{
					ss << "vector " << i << " :";
					++i;
					for (auto& vi : *v)
					{
						ss << " " << vi.Value;
					}
					ss << std::endl;
				}
				return ss.str();
			}

		protected:
			std::vector<std::unique_ptr<std::vector<Node>>> _StorageList;
			int _VectorCapacity = 4096;
			int _WorkingVector = -1;
		};
	};
}