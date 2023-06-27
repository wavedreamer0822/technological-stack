#pragma once
#include "FvMesh.h"
#include "PhysicalCenter.h"
#include "SolveCenter.h"
#include "ComputeTask.h"
#include "StepsCenter.h"
#include "MonitorCenter.h"
#include "ExcuteCenter.h"
namespace LxCFD
{
   class AppRes
   {
   public:
      static std::unique_ptr<PhysicalCenter> PhysicalCenter;
      static std::unique_ptr<FvMesh> FvMesh;
      static std::unique_ptr<ComputeTask> ComputeTask;
      static std::unique_ptr<StepsCenter> StepsCenter;
      static std::unique_ptr<SolveCenter> SolveCenter;
      static std::unique_ptr<MonitorCenter> MonitorCenter;
      static std::unique_ptr<ExcuteCenter> ExcuteCenter;
   };
}