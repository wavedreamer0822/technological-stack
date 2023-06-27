#include "TwoCubeCase.h"
#include "FluentMesh.h"
#include "VTUWriter.h"
#include "TestMonitor.h"
#include "ExcuteSaveFile.h"
namespace LxCFD
{
    TwoCubeCase::TwoCubeCase(int ID, const std::string &fileFolder) : ExampleBase(ID, fileFolder)
    {
        Description = "两固体区域区域耦合导热";
    }
    void TwoCubeCase::RunCase()
    {
        std::string fileName = "Case1-2Zone4w";
        try
        {
            {
                FluentMesh fmesh;
                fmesh.ReadFile(FileFolder + fileName + ".msh");
            }
            {
                AppRes::FvMesh->PrepareMeshData();
            }
            {
                //1.创建物理模型
                auto physical_1 = std::shared_ptr<PhysicalModel>(new PhysicalModel());
                physical_1->SetPhysicalType(PhysicalTypes::Solid);
                physical_1->IsEnergyEnabled = true;
                AppRes::PhysicalCenter->PhysicalModels.push_back(physical_1);

                auto physical_2 = std::shared_ptr<PhysicalModel>(new PhysicalModel());
                physical_2->SetPhysicalType(PhysicalTypes::Solid);
                physical_2->IsEnergyEnabled = true;
                physical_2->MaterialData->ThermalConductivity = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(400));
                AppRes::PhysicalCenter->PhysicalModels.push_back(physical_2);
                //2.设置区域属性及边界条件
                FvZone &zone_1 = FineZone("BODY1");
                zone_1.PhysicalModel = physical_1;
                FvThread &thread_in = FindThread(zone_1, "IN");
                thread_in.WallThermalType = WallThermalTypes::FixHeatFlux;
                thread_in.HeatFlux = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1000));

                FvZone &zone_2 = FineZone("BODY2");
                zone_2.PhysicalModel = physical_2;
                FvThread &thread_out = FindThread(zone_2, "OUT");
                thread_out.WallThermalType = WallThermalTypes::FixTemperature;
                thread_out.Temperature = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(300));

                FvContact &contact = FineContact("CONTACT");
                contact.IsEnabled = true;
                contact.ThermalConductivity = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(200));
                contact.Thickness = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1));
                contact.EnergySource = std::unique_ptr<ValueBase<double>>(new Value1Const::Double(800));
                //3.设置计算参数进行计算
                //MultiThreads::SetThreadsCout(2);
                AppRes::StepsCenter->SteadyStep.MaxSteps = 100;
                std::unique_ptr<UserMonitorBase> monitor = std::unique_ptr<UserMonitorBase>(new TestMonitor());
                AppRes::MonitorCenter->UserMonitors.push_back(std::move(monitor));
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
}