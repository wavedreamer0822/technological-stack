#pragma once
#include <vector>
#include "MultiThreads.h"
#include "AMGInZone.h"
#include "AMGInContact.h"
#include "MatrixBase.h"
#include "ConnectBase.h"
namespace LxCFD
{
	class LinearSolverBase
	{
	public:
		template <typename T1, typename T2>
		void SolveByJacobi(std::vector<T1*>& zones, std::vector<T2*>& contacts)
		{
			if (contacts.size() > 0)
			{
				MultiThreads::RunCalTasks(
					[&](int taskIndex)
					{
						for (auto& c : contacts)
						{
							c->Copy_xArray(taskIndex);
						}
					});
			}
			MultiThreads::RunCalTasks(
				[&](int taskIndex)
				{
					for (auto& z : zones)
					{
						z->CalByJacobi_Step1(taskIndex);
					}
				});
			if (contacts.size() > 0)
			{
				MultiThreads::RunCalTasks(
					[&](int taskIndex)
					{
						for (auto& c : contacts)
						{
							c->Copy_xCommonArray(taskIndex);
						}
					});
			}
			MultiThreads::RunCalTasks(
				[&](int taskIndex)
				{
					for (auto& z : zones)
					{
						z->CalByJacobi_Step2(taskIndex);
					}
				});
		}
		template <typename T1, typename T2>
		void CalResidual(std::vector<T1*>& zones, std::vector<T2*>& contacts)
		{
			if (contacts.size() > 0)
			{
				MultiThreads::RunCalTasks(
					[&](int taskIndex)
					{
						for (auto& c : contacts)
						{
							c->Copy_xArray(taskIndex);
						}
					});
			}
			MultiThreads::RunCalTasks(
				[&](int taskIndex)
				{
					for (auto& z : zones)
					{
						z->CalResidual(taskIndex);
					}
				});
		}
		template <typename T1, typename T2>
		void SolveByBiCG(std::vector<T1*>& zones, std::vector<T2*>& contacts)
		{
			if (contacts.size() > 0)
			{
				MultiThreads::RunCalTasks([&](int taskIndex)
					{
						for (auto& c : contacts)
						{
							c->Copy_xArray(taskIndex);
						}
					});
			}
			MultiThreads::RunCalTasks([&](int taskIndex)
				{
					for (auto& z : zones)
					{
						z->Initialize_Step1_r0rp1rho(taskIndex);
					}
				});
			if (BiCGBase::Initialize_Step2())
			{
				SolveByJacobi(zones, contacts);
			}
			else
			{
				for (int i1 = 1;; ++i1)
				{
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_yArray(taskIndex);
							}
						});
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& c : contacts)
							{
								c->Copy_yArray(taskIndex);
							}
						});
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_vArray_alpha1(taskIndex);
							}
						});
					if (BiCGBase::Cal_alpha())
						return;
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_sArray(taskIndex);
							}
						});
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_zArray(taskIndex);
							}
						});
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& c : contacts)
							{
								c->Copy_zArray(taskIndex);
							}
						});
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_tArray_omega1(taskIndex);
							}
						});
					if (BiCGBase::Cal_omega())
						return;
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_xArray(taskIndex);
							}
						});
					//检查收敛
					if (i1 >= BiCGIteNum)
					{
						return;
					}
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_rArray(taskIndex);
							}
						});
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_rhoPart1(taskIndex);
							}
						});
					if (BiCGBase::Cal_rhobeta())
						return;
					MultiThreads::RunCalTasks([&](int taskIndex)
						{
							for (auto& z : zones)
							{
								z->Cal_pArray(taskIndex);
							}
						});
				}
			}
		}

	protected:
		int MaxCoarseLevel = 0;
		std::vector<AMGInZone*> AMGsInZone;
		std::vector<AMGInContact*> AMGsInContact;
		std::vector<int> VariableCount;
		template <typename T2>
		void AMG_V(std::vector<T2*>& connects)
		{
			while (AMGBase::SolvingLevel < MaxCoarseLevel)
			{
				iniAndRestrict(connects);
				/*        for (int i1 = 0; i1 < 8; i1++) {
							SolveByJacobi(AMGsInZone, AMGsInContact);
						}   */
				SolveByBiCG(AMGsInZone, AMGsInContact);
			}
			while (AMGBase::SolvingLevel > AMG_V_StartLevel)
			{
				SolveByJacobi(AMGsInZone, AMGsInContact);
				prolong();
			}
		}
		template <typename T2>
		void AMG_F(std::vector<T2*>& connects)
		{
			while (AMGBase::SolvingLevel < MaxCoarseLevel)
			{
				iniAndRestrict(connects);
			}
			SolveByBiCG(AMGsInZone, AMGsInContact);
			prolong();
			iniVStartLevel();
			setIsUpdateAFalse();
			while (AMG_V_StartLevel >= 0)
			{
				SolveByBiCG(AMGsInZone, AMGsInContact);
				AMG_V(connects);
				SolveByBiCG(AMGsInZone, AMGsInContact);
				prolong();
				iniVStartLevel();
			}
		}
		template <typename T1, typename T2>
		void LinkAMG(std::vector<T1*>& scalars, std::vector<T2*>& connects)
		{
			if (AMGsInZone.size() != scalars.size() || AMGsInContact.size() != connects.size())
				throw std::invalid_argument("AMG求解器和待求解方程数量不同");
			for (std::size_t i1 = 0; i1 < AMGsInZone.size(); ++i1)
			{
				AMGsInZone.at(i1)->LinkToMatrix(scalars.at(i1));
			}
			for (std::size_t i1 = 0; i1 < AMGsInContact.size(); ++i1)
			{
				AMGsInContact.at(i1)->LinkToMatrix(connects.at(i1));
			}
			AMGBase::SolvingLevel = -1;
			iniVStartLevel();
		}

	private:
		volatile int AMG_V_StartLevel; //对于V循环，该值为-1
		volatile int BiCGIteNum = 8;
		void iniVStartLevel();
		void restrict();
		void prolong();
		void setIsUpdateAFalse();
		template <typename T2>
		void iniAndRestrict(std::vector<T2*>& connects)
		{
			if (AMGBase::SolvingLevel == -1)
			{
				if (connects.size() > 0)
				{
					MultiThreads::RunCalTasks(
						[&](int taskIndex)
						{
							for (auto& c : connects)
							{
								c->Copy_xArray(taskIndex);
							}
						});
				}
			}
			else
			{
				if (AMGsInContact.size() > 0)
				{
					MultiThreads::RunCalTasks(
						[&](int taskIndex)
						{
							for (auto& c : AMGsInContact)
							{
								c->Copy_xArray(taskIndex);
							}
						});
				}
			}
			restrict();
		}
	};
}