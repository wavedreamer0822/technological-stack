#pragma once
#include "MatrixBase.h"
#include "TransientDataBase.h"

namespace LxCFD
{
    class EquationBase : public MatrixBase
    {

    public:
        class TransientScalar :public TransientDataBase
        {
        protected:
            EquationBase *Matrix;
            std::vector<double> *x;
            std::vector<double> *b;
            std::vector<double> *ADiag;
            std::vector<FvCell> *Cells;

        public:
            std::shared_ptr<Value1Base<double>> Trans;
            std::shared_ptr<Value1Base<double>> Density;
            std::shared_ptr<std::vector<double>> RhoVolPhi_o;
            std::shared_ptr<std::vector<double>> RhoVolPhi_oo;

            void CheckCreate(EquationBase *Matrix);
            void SetTransient(std::shared_ptr<Value1Base<double>> trans, std::shared_ptr<Value1Base<double>> density);
            void SetAb_ImplicitTrans(int taskIndex);
            void SetAb_ExplicitTrans(int taskIndex);
            virtual void SaveOldValue(int taskIndex) override;
            virtual void PrepareToSave() override;
            virtual void Initialize() override;
        };

        std::unique_ptr<TransientScalar> TransData;
        virtual void Set_x_Bound(int taskIndex) = 0;
        virtual void SetAb_Step1(int taskIndex) = 0;
        virtual void SetAb_Step2(int taskIndex) = 0;
        virtual void Update_x_Bound(int taskIndex) = 0;
        void CopyFromOldEquation(std::unique_ptr<EquationBase> oldEquation);
        void SetZone_TransTerm(bool isEnable, std::shared_ptr<Value1Base<double>> trans, std::shared_ptr<Value1Base<double>> density);
    };
}