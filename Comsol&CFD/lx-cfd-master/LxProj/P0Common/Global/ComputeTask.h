#pragma once

namespace LxCFD
{
   class ComputeTask
   {
   public:
      void RunForceInitialization();
      void RunComputation();

   protected:
      bool _IsForceInitialize = false;
      void runComputation();
      void hostTask();
      void run_steadyCal();
      void run_transientExplicit();
      void run_transientImplicit();
      void moveNext_transient();
   };
}