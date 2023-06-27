#pragma once
#include <iostream>
#include "IndexRecorder.h"
#include "LxTool.h"
namespace LxCFD
{
	class IndexNumber
	{
	public:
		IndexNumber();
		IndexNumber(int startCellID, int endCellID, int startFaceID, int endFaceID);
		IndexRecorder CellIDs;
		IndexRecorder FaceIDs;
		std::string ToString();
		void Print();
	};
}