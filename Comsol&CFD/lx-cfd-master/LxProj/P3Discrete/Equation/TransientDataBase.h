#pragma once
#include "IInitializable.h"

namespace LxCFD
{
    class TransientDataBase : public IInitializable
    {
    public:
        enum class TransientDataStates
        {
            None,
            Only_o,
            Both_o_oo
        };
        static bool IsSecondOrder;
        static double Factor_Phi_1stOrder;
        static double Factor_Phi_2ndOrder;
        static double Factor_PhiO_2ndOrder;
        static double Factor_PhiOO_2ndOrder;

        virtual bool GetIsInitialized() override;
        virtual void SetIsInitialized(bool isInitialized) override;
        virtual void SaveOldValue(int taskIndex) = 0;
        virtual void PrepareToSave() = 0;

    protected:
        TransientDataStates TransientDataState = TransientDataStates::None;
    };
}