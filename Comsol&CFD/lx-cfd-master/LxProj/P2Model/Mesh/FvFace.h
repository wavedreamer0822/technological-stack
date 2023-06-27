#pragma once
#define FaceCorOption 0
#include <vector>
#include "ShortArray.h"
#include "Vector3d.h"
#include "ONPair.h"

namespace LxCFD
{
	struct FvCell;
	struct FvFace
	{
	public:
		FvFace();
		// FvFace(const std::vector<int> &nodes, int c0, int c1, bool isRightHand);
		//拓扑信息
		ShortArray::Shallow NodeIDs;
		int OSideCell = 0;
		int NSideCell = 0;
		//几何信息
		Vector3d Center;
		Vector3d Normal; //lenth为面的面积
		double Area = 0;
		Vector3d OToN; //由cell0 中心指向cell1中心的矢量
		double OToNLength = 0;
		//用于计算
		double gOwner; //owner cell 到面的距离 投影到ownerToNeighbor，然后除以ownerToNeighbor的长度
		double gDiff = 0;
#if FaceCorOption == 0
		inline double GetgT()
		{
			return gDiff;
		} //计算非正交修正时用到
#else
		double _gT = 0;
		inline double GetgT()
		{
			return _gT;
		} //计算非正交修正时用到
#endif
		void Set(ShortArray::Deep& store, const ShortArray::Shallow& nodes, int c0, int c1, bool isRightHand);
		void CalGeometryInFace(std::vector<Vector3d>& points);
		void CalGeometryAcrossFace_inner(std::vector<FvCell>& cells);
		void CalGeometryAcrossFace_bound(std::vector<FvCell>& cells);
		Vector3d CalONGradient_DistanceWeighted(std::vector<double>& phi); //求解Grad 梯度时使用
		ONPair GetONCellID();
		double CalAverage(std::vector<double>& phi);
		Vector3d CalAverage(std::vector<Vector3d>& gradPhi);
		Vector3d CalCFCorrectedGradient_inner(std::vector<Vector3d>& gradPhi, std::vector<double>& phi);
		Vector3d CalCFCorrectedGradient_bound(std::vector<Vector3d>& gradPhi, std::vector<double>& phi);
		Vector3d CalCFGradCorrection_inner(std::vector<Vector3d>& gradPhi, std::vector<double>& phi);
		Vector3d CalCFGradCorrection_bound(std::vector<Vector3d>& gradPhi, std::vector<double>& phi);
		double CalNonOrthogonalityCorrection_inner(std::vector<Vector3d>& gradPhi, std::vector<double>& phi);
		double CalNonOrthogonalityCorrection_bound(std::vector<Vector3d>& gradPhi, std::vector<double>& phi);
		double CalNonOrthogonalityCorrection_bound(double& out_a, double& out_b, std::vector<Vector3d>& gradPhi, std::vector<double>& phi, std::vector<FvCell>& cells); //只写了匹配minCorrection的//虽然不是minCorrect也可能能用，但应该重新推导公式，进行源项线性化

	private:
		void CalTriangleGeometry(Vector3d& out_CenterMultiply3, Vector3d& out_AreaMultiply2, const Vector3d& p0, const Vector3d& p1, const Vector3d& p2);
		void calO2N(std::vector<FvCell>& cells);
		Vector3d calCFCorrectPart(const Vector3d& aveGrad, std::vector<double>& phi); //求解C F 网格值修正部分
		double calNonOrthogonalityCorrection(const Vector3d& aveGrad, std::vector<double>& phi);
	};
}