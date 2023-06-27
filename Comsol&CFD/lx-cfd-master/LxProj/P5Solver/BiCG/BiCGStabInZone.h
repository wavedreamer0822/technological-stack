#pragma once
#include <vector>
#include "BiCGBase.h"
#include "IProvideVariableCount.h"
#include "IndexNumber.h"
namespace LxCFD
{
    class BiCGStabInZone : public BiCGBase
    {
    public:
        std::vector<double> *r0;
        std::vector<double> *r; //s“≤”√r¥Ê¥¢
        std::vector<double> p;
        std::vector<double> v;
        std::vector<double> y;
        std::vector<double> z;
        std::vector<double> t;

        void CreateLocal(IProvideVariableCount &variableCount);
        void CreateCommon(std::vector<double> *rCommon, std::vector<double> *r0Common);
        void Initialize0ValueInArray(IndexNumber &indexNumber, int taskIndex);
        void Cal_r_Dot_r0(IndexNumber &indexNumber, int taskIndex);
        void Cal_xArray(IndexNumber &indexNumber, std::vector<double> &x, int taskIndex);
        void Cal_sArray(IndexNumber &indexNumber, int taskIndex);
        void Cal_rArray(IndexNumber &indexNumber, int taskIndex);
        void Cal_pArray(IndexNumber &indexNumber, int taskIndex) ;
        void Cal_yArray(IndexNumber &indexNumber, std::vector<double> &ADiag, int taskIndex);
        void Cal_zArray(IndexNumber indexNumber, std::vector<double>& ADiag, int taskIndex);

    protected:
        void Cal_rMinus(IndexNumber &indexNumber, double factor, std::vector<double> &subtrahend, int taskIndex);
        void DInversePrecond(IndexNumber &indexNumber, std::vector<double> &left, std::vector<double> &ADiag, std::vector<double> &right, int taskIndex);
    };
}