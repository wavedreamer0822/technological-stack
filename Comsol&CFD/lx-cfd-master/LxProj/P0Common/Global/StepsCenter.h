#pragma once
#include "IReset.h"
namespace LxCFD
{
   class StepsCenter : public IReset
   {
   public:
      struct StepsAndStop
      {
      public:
         int StepsCount = 0;
         int MaxSteps = 2;
         void ResetStopRule();
         void AddStopRule(bool isForce, bool isStop);
         bool IsContinue();

      protected:
         bool isStop_Or = false;
         bool isStop_And = true;
         bool isStop_And_isUsed = false;
      };

      StepsAndStop SteadyStep;
      StepsAndStop TransientStep;
      int TotalStepCount;
      virtual void Reset(ResetTypes resetType) override;
      void MoveNextStep_Steady();
      void MoveNextStep_Transient();
   };
}