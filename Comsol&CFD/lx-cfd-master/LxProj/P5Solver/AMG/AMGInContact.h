#pragma once
#include "MGContact.h"
#include "BiCGStabInZone.h"
#include "MGMeshCreator.h"
#include "AMGInZone.h"

namespace LxCFD
{
   class AMGInContact : public AMGBase, public ISolvableContact
   {
   public:
      std::vector<std::unique_ptr<MGContact>> MGContacts;
      BiCGStabInZone *O_BiCGSolver;
      BiCGStabInZone *N_BiCGSolver;
      void Create(IProvideContactTopology *startContact, MGMeshCreator &commonData, AMGInZone &oZoneAMG, AMGInZone &nZoneAMG, int oThreadID, int nThreadID);
      void LinkToMatrix(IAMGSolvableContact *connect);
      void Restrict(int taskIndex);
      void Copy_xArray(int taskIndex);
      void Copy_xCommonArray(int taskIndex);
      void Copy_yArray(int taskIndex);
      void Copy_zArray(int taskIndex);
   };
}