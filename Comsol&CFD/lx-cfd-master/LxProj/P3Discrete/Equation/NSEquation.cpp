#include "NSEquation.h"
#include "AppRes.h"
namespace LxCFD
{
	void NSEquation::BoundaryFixValueWall::SetFixValue(std::shared_ptr<Value1Base<double>> fixValue)
	{
		FixValue = fixValue;
		SetxState.SetState(fixValue->IsConstant());
	}
	void NSEquation::BoundaryFlowValue::SetParameter(std::shared_ptr<Value1Base<double>> baseValue)
	{
		BaseValue = baseValue;
	}
	void NSEquation::BoundaryFixFlux::SetParameter(std::shared_ptr<Value1Base<double>> flux)
	{
		Flux = flux;
	}
	void NSEquation::SetZone_CommonTerm(std::shared_ptr<Value1Base<double>> gamma, std::shared_ptr<ValueBase<double>> source, std::shared_ptr<Value1Base<double>> iniValue, double relaxFactor)
	{
		clear_eFlags();
		FixValueWallBounds.clear();
		SymmetryBounds.clear();
		FlowValueBounds.clear();
		FluxBounds.clear();
		CoupledWalls.clear();

		Gamma = gamma;
		Source = source;
		IniValue = iniValue;
		RelaxFactor = relaxFactor;
	}
	void NSEquation::SetZone_ConvTerm(std::shared_ptr<Value1Base<double>> conv, ConvectionSchemes convectionScheme, MassFluxBase& massBase)
	{
		Conv = conv;
		ConvectionScheme = convectionScheme;
		switch (convectionScheme)
		{
		case ConvectionSchemes::MUSCL_DC:
			if (!(dynamic_cast<MUSCL_DC*>(CalgCfPhir.get())))
				CalgCfPhir = std::unique_ptr<ICalgCfPhir>(new MUSCL_DC()); // new MUSCL_DC();
			break;
		case ConvectionSchemes::OSHER_DC:
			if (!(dynamic_cast<OSHER_DC*>(CalgCfPhir.get())))
				CalgCfPhir = std::unique_ptr<ICalgCfPhir>(new OSHER_DC());
			break;
		default:
			break;
		}
		MassFlux = massBase.MassFlux.get();
		MassImbalance = massBase.MassImbalance.get();
		VelocityDirectionCorrection = massBase.VelocityDirectionCorrection.get();
	}
	void NSEquation::SetBoundary_fixValue(std::shared_ptr<Value1Base<double>> fixValue, FvThread& thread)
	{
		std::unique_ptr<BoundaryFixValueWall> boundaryFixValue = std::unique_ptr<BoundaryFixValueWall>(new BoundaryFixValueWall());
		boundaryFixValue->SetHead(thread);
		boundaryFixValue->SetFixValue(fixValue);

		FixValueWallBounds.push_back(std::move(boundaryFixValue));
		e_FixValue.push_back(thread.ID);
	}
	void NSEquation::SetBoundary_symmetry(FvThread& thread)
	{
		std::unique_ptr<BoundaryScalarSymmetry> boundarysymmetry = std::unique_ptr<BoundaryScalarSymmetry>(new BoundaryScalarSymmetry());
		boundarysymmetry->SetHead(thread);

		SymmetryBounds.push_back(std::move(boundarysymmetry));
		e_ALUO0.push_back(thread.ID);
	}
	void NSEquation::SetBoundary_flow(std::shared_ptr<Value1Base<double>> baseValue, FvThread& thread)
	{
		std::unique_ptr<BoundaryFlowValue> flow = std::unique_ptr<BoundaryFlowValue>(new BoundaryFlowValue());
		flow->SetHead(thread);
		flow->SetParameter(baseValue);

		FlowValueBounds.push_back(std::move(flow));
		e_FixValue.push_back(thread.ID);
	}
	void NSEquation::SetBoundary_Coupled_Wall(FvThread& thread)
	{
		std::unique_ptr<BoundaryHeadBase> wall = std::unique_ptr<BoundaryHeadBase>(new BoundaryHeadBase());
		wall->SetHead(thread);

		CoupledWalls.push_back(std::move(wall));
		e_Couple.push_back(thread.ID);
	}

	void NSEquation::Initialize()
	{
		MultiThreads::RunCalTasks([this](int i)
			{ initialize(i); });
	}
	void NSEquation::initialize(int taskIndex)
	{
		set_x(*IniValue, *InnerIndex, taskIndex);
		Set_x_Bound(taskIndex);
		for (auto& b : SymmetryBounds)
		{
			set_x(*IniValue, *b->ThreadIndex, taskIndex);
		}
		for (auto& b : FlowValueBounds)
		{
			set_x(*b->BaseValue, *b->ThreadIndex, taskIndex);
		}
		for (auto& b : CoupledWalls)
		{
			set_x(*IniValue, *b->ThreadIndex, taskIndex);
		}
	}
	void NSEquation::Set_x_Bound(int taskIndex)
	{
		for (auto& b : FixValueWallBounds)
		{
			if (b->SetxState.GetIsNeedToCal(taskIndex))
			{
				set_x(*b->FixValue, *b->ThreadIndex, taskIndex);
			}
		}
	}
	void NSEquation::SetAb_Step1(int taskIndex)
	{
		//计算内部面 A_LU
		switch (ConvectionScheme)
		{
		case ConvectionSchemes::FirstOrderUpwind:
		default:
			set_Ab_Upwind_inner(taskIndex);
			break;
		case ConvectionSchemes::SecondOrderUpwind:
			set_Ab_SOU_inner(taskIndex);
			break;
		case ConvectionSchemes::OSHER:
			set_Ab_OSHER_inner(taskIndex);
			break;
		case ConvectionSchemes::MUSCL:
			set_Ab_MUSCL_inner(taskIndex);
			break;
		case ConvectionSchemes::OSHER_DC:
		case ConvectionSchemes::MUSCL_DC:
			set_Ab_TVD_DC_inner(taskIndex);
			break;
		}
		for (auto& b : FixValueWallBounds)
		{
			set_Ab_boundOwner_DiffPart(*b->ThreadIndex, taskIndex);
		}
		for (auto& b : SymmetryBounds)
		{
			set_A_boundOwner_0(*b->ThreadIndex, taskIndex);
		}
		for (auto& b : FlowValueBounds)
		{
			set_Ab_bound_flow(*b->ThreadIndex, taskIndex);
		}
	}
	void NSEquation::SetAb_Step2(int taskIndex)
	{
		if (auto* source1 = dynamic_cast<Value1Base<double> *>(Source.get()))
		{
			setAb_step2(source1, taskIndex);
		}
		else if (auto* source2 = dynamic_cast<Value2Base<double> *>(Source.get()))
		{
			setAb_step2(source2, taskIndex);
		}
		else
		{
			LxConsole::Error("未知的源项类型");
		}
		//if (FixValueWallBounds.size() == 2 && AppRes::StepsCenter->SteadyStep.StepsCount > 30)
		//{
		//	using namespace std;
		//	double maxvalue = numeric_limits<double>::min();
		//	int cellID;
		//	for (int i1 = 0; i1 <= InnerIndex->CellIDs.End; ++i1)
		//	{
		//		if (x->at(i1) > maxvalue) {
		//			maxvalue = x->at(i1);
		//			cellID = i1;
		//		}
		//	}
		//	if(maxvalue < 410) return;
		//	FvCell& cell = Cells->at(cellID);
		//	cout << " cellID=" << cellID << endl;
		//	cout << " x=" << x->at(cellID) << " massImbalance=" << MassImbalance->at(cellID) << " ADiag=" << ADiag->at(cellID) << " b=" << b->at(cellID) << endl;
		//	double xnew = b->at(cellID);
		//	for (auto& f : cell.OFaces) {
		//		cout << " ofaceID=" << f << endl;
		//		cout << " xo=" << x->at(Faces->at(f).NSideCell) << " ALUO=" << ALUO->at(f) << " massFlux=" << MassFlux->at(f) << endl;
		//		xnew -= ALUO->at(f) * x->at(Faces->at(f).NSideCell);
		//	}
		//	for (auto& f : cell.NFaces) {
		//		cout << " nfaceID=" << f << endl;
		//		cout << " xn=" << x->at(Faces->at(f).OSideCell) << " ALUN=" << ALUN->at(f) << " massFlux=" << MassFlux->at(f) << endl;
		//		xnew -= ALUN->at(f) * x->at(Faces->at(f).OSideCell);
		//	}
		//	cout << " xnew=" << xnew / ADiag->at(cellID) << endl;
		//}
	}
	void NSEquation::Update_x_Bound(int taskIndex)
	{
		for (auto& b : SymmetryBounds)
		{
			updateBound_grad0(*b->ThreadIndex, taskIndex);
		}
		for (auto& b : FlowValueBounds)
		{
			set_x_flow(*b->BaseValue, *b->ThreadIndex, taskIndex);
		}
	}
}