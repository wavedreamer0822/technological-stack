#pragma once
#include "ExampleBase.h"
#include "Value1Base.h"
namespace LxCFD
{
    class UserDefineSourceCase : public ExampleBase
    {
    public:
        class UserSource : public Value1Base<double>
        {
        public:
            UserSource(const Vector3d &heatCenter, double radius);
            Vector3d HeatCenter;
            double Radius;
            std::vector<FvCell> *Cells;
            virtual double GetCellValue(int cellIndex) override;
            virtual std::shared_ptr<Value1Base<double>> GetCopy(HeadBase *zoneOrContact) override;
        };
        UserDefineSourceCase(int ID,const std::string &fileFolder);
        virtual void RunCase() override;
    };
}