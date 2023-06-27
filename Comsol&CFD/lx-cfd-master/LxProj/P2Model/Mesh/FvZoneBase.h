#pragma once
#include <vector>
#include <memory>
#include "HeadBase.h"
#include "FvCell.h"
#include "IndexNumber.h"
#include "FvThread.h"
#include "IProvideZoneTopology.h"
#include "AMGInZone.h"
#include "BiCGStabInZone.h"
#include "IPrepareMesh.h"
namespace LxCFD
{
	class FvZoneBase : public HeadBase, public IProvideZoneTopology, public IProvideVariableCount, public IPrepareMesh, public MeshSelector
	{
	public:
		//local
		std::shared_ptr<std::vector<Vector3d>> Nodes;
		std::vector<FvCell> Cells;
		std::vector<FvFace> Faces;
		ShortArray::Deep ShallowArrayStorage;
		double Volumn;
		std::vector<double> CellCommonArray;
		std::vector<double> FaceCommonArray;
		IndexNumber InnerIndex;
		IndexNumber TotalIndex;
		AMGInZone AMGSolver;
		BiCGStabInZone BiCGSolver;
		std::vector<std::unique_ptr<FvThread>> BoundThreads;
		virtual void PrepareMeshData() override;
		virtual ShortArray::Shallow& GetCellOFaces(int CellIndex) override;
		virtual ShortArray::Shallow& GetCellNFaces(int CellIndex) override;
		virtual int GetFaceOSideCell(int FaceIndex) override;
		virtual int GetFaceNSideCell(int FaceIndex) override;
		virtual ONPair GetONCellID(int FaceIndex) override;
		virtual IndexNumber& GetInnerIndex() override;
		virtual IndexNumber& GetTotalIndex() override;
		virtual int GetThreadCount() override;
		virtual IndexNumber& GetThreadIndex(int threadID) override;
		virtual int GetVariableCount() override;

	protected:
		void CreatCells();
		void CalZoneGeometry();
		void CalTotalVolumnArea();
	};
}
// struct TempCell
// {
// public:
//     TempCell()
//     {
//         OFaces.reserve(10);
//         NFaces.reserve(10);
//     }
//     std::vector<int> OFaces;
//     std::vector<int> NFaces;
// };