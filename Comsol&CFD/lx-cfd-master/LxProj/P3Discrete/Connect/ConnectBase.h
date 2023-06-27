#pragma once
#include "ConnectHeadBase.h"
#include "ISolvableContact.h"
#include "PairMatrix.h"
#include "EquationBase.h"
#include "IBiCGStabSolvableContact.h"
#include "IAMGSolvableContact.h"
namespace LxCFD
{
   class ConnectBase : public ConnectHeadBase, public ISolvableContact, public IAMGSolvableContact
   {
   public:
      std::unique_ptr<std::vector<PairMatrix>> ADLUb;
      virtual void CheckCreate(FvContact &contact) override;
      void SetArray(EquationBase &OMatrix, EquationBase &NMatrix);
      virtual void Copy_xCommonArray(int taskIndex) override;
      virtual void Copy_xArray(int taskIndex) override;
      virtual void Restrict_ALU(double &out_ALUO, double &out_ALUN, MGPair &mgPair) override;
      virtual void Copy_yArray(int taskIndex) override;
      virtual void Copy_zArray(int taskIndex) override;
      virtual void SetAb_Step1(int taskIndex) = 0;
      virtual void Update_x_Bound(int taskIndex) = 0;

   protected:
      EquationBase *O_Matrix;
      EquationBase *N_Matrix;
      std::vector<double> *O_x;
      std::vector<double> *N_x;
      std::vector<double> *O_ALUN;
      std::vector<double> *N_ALUN;
      std::vector<double> *O_ALUO;
      std::vector<double> *N_ALUO;
      std::vector<Vector3d> *O_grad;
      std::vector<Vector3d> *N_grad;
      std::vector<double> *O_xCommon;
      std::vector<double> *N_xCommon;
      std::vector<double> *O_bFaceCommon;
      std::vector<double> *N_bFaceCommon;
      void CopyBound(std::vector<double> &OArray, std::vector<double> &NArray, int taskIndex);
   };
}