#pragma once
#include <vector>
#include <iostream>
#include "ShortArray.h"

namespace LxCFD
{
	struct MGCell
	{
	public:
		ShortArray::Shallow OFaces;
		ShortArray::Shallow  NFaces;
		ShortArray::Shallow  FineCells;
		ShortArray::Shallow  InnerFineFaces;
		//待求解矩阵的系数
		double r = 0;
		//void Set(ShallowArrayStorage &store, const std::vector<int> &oFaces, const std::vector<int> &nFaces, const std::vector<int> &fineCells, const std::vector<int> &innerFineFaces);
	};
}
// MGCell(const std::vector<int> &oFaces, const std::vector<int> &nFaces, const std::vector<int> &fineCells, const std::vector<int> &innerFineFaces)
//     : OFaces(oFaces), NFaces(nFaces), FineCells(fineCells), InnerFineFaces(innerFineFaces) {}
