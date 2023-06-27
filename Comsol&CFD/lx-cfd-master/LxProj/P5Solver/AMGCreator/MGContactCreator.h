#pragma once
#include "MGCellTemp.h"
#include "IProvideContactTopology.h"
#include "MGZone.h"
#include "MGContact.h"
#include "QueueTool.h"
namespace LxCFD
{
	class MGContactCreator
	{
	public:
		std::vector<MGCellTemp>* contactTempCells;

		LinkArray<MGFaceTemp>::Deep LinkArray_MGFaceTemp;
		LinkArray<int>::Deep LinkArray_Int;
		QueueTool  QueueTool_O;
		QueueTool  QueueTool_N;

		IProvideContactTopology* fineContact;
		std::vector<int> InOCoarseCell;
		std::vector<int> InNCoarseCell;
		MGContact* coarseContact;
		int tempCellsStart;

		std::unique_ptr<MGContact> CreateMGContact(IProvideContactTopology* fineContact, MGZone* OZone, MGZone* NZone, IndexNumber* OIndex, IndexNumber* NIndex);
		void makeFlag();
		void addContactFaceToStorage();
		void add(int i1, ONPair onnew);
		void splitContactCoarseFaceFromStorage();
		void checkTopology();
	};
}