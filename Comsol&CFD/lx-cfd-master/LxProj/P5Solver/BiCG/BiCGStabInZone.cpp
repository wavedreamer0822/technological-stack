#include "BiCGStabInZone.h"
#include "ThreadsMath.h"
namespace LxCFD
{
    void BiCGStabInZone::CreateLocal(IProvideVariableCount &variableCount)
    {
        int length = variableCount.GetVariableCount();
        p.clear();
        v.clear();
        y.clear();
        z.clear();
        t.clear();
        p.resize(length);
        v.resize(length);
        y.resize(length);
        z.resize(length);
        t.resize(length);
    }
    void BiCGStabInZone::CreateCommon(std::vector<double> *rCommon, std::vector<double> *r0Common)
    {
        r = rCommon;
        r0 = r0Common;
    }
    void BiCGStabInZone::Initialize0ValueInArray(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            r->at(i1) = 0;
            r0->at(i1) = 0;
            p.at(i1) = 0;
            v.at(i1) = 0;
            y.at(i1) = 0;
            z.at(i1) = 0;
            t.at(i1) = 0;
        }
    }
    void BiCGStabInZone::Cal_r_Dot_r0(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        double temp = 0;
        for (; i1 < endp1; ++i1)
        {
            temp += r0->at(i1) * r->at(i1);
        }
        ThreadsMath::AddToSum(temp);
    }

    void BiCGStabInZone::Cal_xArray(IndexNumber &indexNumber, std::vector<double> &x, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            x.at(i1) += alpha * y.at(i1) + omega * z.at(i1);
        }
    }
    void BiCGStabInZone::Cal_sArray(IndexNumber &indexNumber, int taskIndex)
    {
        Cal_rMinus(indexNumber, alpha, v, taskIndex);
    }
    void BiCGStabInZone::Cal_rArray(IndexNumber &indexNumber, int taskIndex)
    {
        Cal_rMinus(indexNumber, omega, t, taskIndex);
    }

    void BiCGStabInZone::Cal_pArray(IndexNumber &indexNumber, int taskIndex) //2
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            p.at(i1) = r->at(i1) + beta * (p.at(i1) - omega * v.at(i1));
        }
    }
    void BiCGStabInZone::Cal_yArray(IndexNumber &indexNumber, std::vector<double> &ADiag, int taskIndex)
    {
        DInversePrecond(indexNumber, y, ADiag, p, taskIndex);
    }

    void BiCGStabInZone::Cal_zArray(IndexNumber indexNumber, std::vector<double> &ADiag, int taskIndex)
    {
        DInversePrecond(indexNumber, z, ADiag, *r, taskIndex);
    }

    void BiCGStabInZone::Cal_rMinus(IndexNumber &indexNumber, double factor, std::vector<double> &subtrahend, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            r->at(i1) -= factor * subtrahend.at(i1);
        }
    }
    void BiCGStabInZone::DInversePrecond(IndexNumber &indexNumber, std::vector<double> &left, std::vector<double> &ADiag, std::vector<double> &right, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            left.at(i1) = right.at(i1) / ADiag.at(i1);
        }
    }
}