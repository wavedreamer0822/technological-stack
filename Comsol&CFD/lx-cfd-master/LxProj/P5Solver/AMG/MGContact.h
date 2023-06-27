#pragma once
#include "IProvideContactTopology.h"
#include "MGZone.h"
#include "MGPair.h"
#include "IAMGSolvableContact.h"
#include "ISolvableContact.h"

namespace LxCFD
{
    class AMGInContact;
    class MGContact : public IProvideContactTopology, public IAMGSolvableContact, public ISolvableContact
    {
    public:
        //local
        IndexNumber InnerIndex;
        std::vector<MGPair> Pairs;
        ShortArray::Deep ShallowArrayStorage;
        //not local
        MGZone *O_Zone;
        IndexNumber *O_Index;
        std::vector<MGCell> *O_Cells;
        std::vector<MGFace> *O_Faces;
        MGZone *N_Zone;
        IndexNumber *N_Index;
        std::vector<MGCell> *N_Cells;
        std::vector<MGFace> *N_Faces;

        virtual ShortArray::Shallow &GetOZoneCellOFaces(int cellIndex) override;
        virtual ShortArray::Shallow &GetNZoneCellOFaces(int cellIndex) override;
        virtual IndexNumber &GetInnerIndex() override;

    public:
        std::vector<double> ALUO;
        std::vector<double> ALUN;
        AMGInContact *InAMGSolver;
        std::vector<double> *O_e;
        std::vector<double> *O_eCommon;
        std::vector<double> *N_e;
        std::vector<double> *N_eCommon;
        IAMGSolvableContact *FinerContact;
        void SetArray(AMGInContact *inAMGSolver);
        void SetFineContact(IAMGSolvableContact *finecontact);
        void Restrict_ALU(int taskIndex);
        virtual void Restrict_ALU(double &out_ALUO, double &out_ALUN, MGPair &mgPair) override;
        virtual void Copy_xArray(int taskIndex) override;
        virtual void Copy_xCommonArray(int taskIndex) override;
        virtual void Copy_yArray(int taskIndex) override;
        virtual void Copy_zArray(int taskIndex) override;

    protected:
        void copyContact(std::vector<double> &OArray, std::vector<double> &NArray, int taskIndex);
    };
}