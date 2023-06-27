#include "UserDefineSourceCase.h"
#include "FluentMesh.h"
#include "ExcuteSaveFile.h"
namespace LxCFD
{
    UserDefineSourceCase::UserDefineSourceCase(int ID, const std::string &fileFolder) : ExampleBase(ID, fileFolder)
    {
        Description = "自定义热源";
    }

    void UserDefineSourceCase::RunCase()
    {
        std::string fileName = "Case2-Cavity";
        try
        {
            //1.读取文件
            {
                FluentMesh fmesh;
                fmesh.ReadFile(FileFolder + fileName + ".msh");
            }
            AppRes::FvMesh->PrepareMeshData();
            {
                //2.设置物理模型
                auto physical = std::shared_ptr<PhysicalModel>(new PhysicalModel());
                physical->SetPhysicalType(PhysicalTypes::Solid);
                physical->IsEnergyEnabled = true;
                physical->MaterialData->ThermalConductivity = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1));
                AppRes::PhysicalCenter->PhysicalModels.push_back(physical);
                //3.设置边界条件
                FvZone &zone = FineZone("SOLID");
                zone.PhysicalModel = physical;

                FvThread &thread_DOWN = FindThread(zone, "DOWN");
                thread_DOWN.WallThermalType = WallThermalTypes::FixTemperature;
                thread_DOWN.Temperature = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(300));

                std::unique_ptr<UserSource> heatSource = std::unique_ptr<UserSource>(new UserSource(Vector3d(0.05, 0.075, 0.005), 0.005));
                zone.EnergySource = std::move(heatSource);
                //3.进行计算参数
                MultiThreads::SetThreadsCout(2);
                AppRes::StepsCenter->SteadyStep.MaxSteps = 100;
                //4.设置文件保存
                std::shared_ptr<ExcuteSaveFile> saveFileTask = std::shared_ptr<ExcuteSaveFile>(new ExcuteSaveFile());
                saveFileTask->FilePath = FileFolder + fileName + ".vtu";
                saveFileTask->ExportScalars.push_back(ScalarTypes::Temperature);
                AppRes::ExcuteCenter->ExcuteAfterAll_Fixed.push_back(saveFileTask);
                //5.执行计算
                AppRes::ComputeTask->RunComputation();
            }
        }
        catch (std::exception &e)
        {
            LxConsole::Error(e.what());
            return;
        }
    }
    UserDefineSourceCase::UserSource::UserSource(const Vector3d &heatCenter, double radius)
    {
        HeatCenter = heatCenter;
        Radius = radius;
    }
    double UserDefineSourceCase::UserSource::GetCellValue(int cellIndex)
    {
        if ((Cells->at(cellIndex).Center - HeatCenter).CalLength() < Radius)
        {
            return 1e6;
        }
        else
        {
            return 0;
        }
    }
    std::shared_ptr<Value1Base<double>> UserDefineSourceCase::UserSource::GetCopy(HeadBase *zoneOrContact)
    {
        if (FvZone *zone = dynamic_cast<FvZone *>(zoneOrContact))
        {
            auto result = std::shared_ptr<UserSource>(new UserSource(HeatCenter, Radius));
            result->Cells = &zone->Cells;
            return result;
        }
        else
        {
            throw std::invalid_argument("未识别区域类型");
        }
    }
}