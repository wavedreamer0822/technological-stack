#pragma once
#include <memory>
#include <atomic>
#include "MassFluxBase.h"
#include "ICalResidual.h"
#include "BoundaryHeadBase.h"
#include "NSEquation.h"
#include "RhieChow_2ndOrderTrans.h"
namespace LxCFD
{
    class PressureCorrectionBasic;
    class PressureSIMPLE;
    class VelocityVector : public MassFluxBase, public ICalResidual
    {
    public:
        class Wall : public BoundaryHeadBase
        {
        public:
            ValueStateLog FluxState{true};
        };
        class NoSlipWall : public Wall
        {
        public:
            std::shared_ptr<Value1Base<Vector3d>> BoundaryVelocity;
            ValueStateLog SetVelState;
            void SetParameter(std::shared_ptr<Value1Base<Vector3d>> boundaryVelocity);
        };
        class Symmetry : public Wall
        {
        };
        class VelocityInlet : public BoundaryHeadBase
        {
        public:
            std::shared_ptr<Value1Base<Vector3d>> Velocity;
            ValueStateLog SetVelState;
            void SetParameter(std::shared_ptr<Value1Base<Vector3d>> velocity);
        };
        class PressureInOut : public BoundaryHeadBase
        {
        public:
            std::shared_ptr<Value1Base<double>> Pressure;
            std::shared_ptr<Value1Base<Vector3d>> Direction; //不需要为单位向量
            ValueStateLog SetPressureState;
            void SetParameter(std::shared_ptr<Value1Base<double>> pressure, std::shared_ptr<Value1Base<Vector3d>> direction);
        };
        class Value3dBoundInVel : public Value1Base<Vector3d>
        {
        public:
            Value3dBoundInVel(std::shared_ptr<Value1Base<double>> value, FvZone &zone);
            std::vector<FvFace> *Faces;
            std::vector<FvCell> *Cells;
            std::shared_ptr<Value1Base<double>> Value;
            virtual Vector3d GetCellValue(int cellIndex) override;
        };
        class Value3dBoundNormalDir : public Value1Base<Vector3d>
        {
        public:
            Value3dBoundNormalDir(FvZone &zone);
            std::vector<FvFace> *Faces;
            virtual Vector3d GetFaceValue(int faceIndex) override;
        };
        class TransientVelocity :public TransientDataBase
        {
        public:
            std::shared_ptr<std::vector<Vector3d>> RhoVel_o;
            std::shared_ptr<std::vector<Vector3d>> RhoVel_oo;
            std::shared_ptr<std::vector<Vector3d>> Vel_o;
            PressureCorrectionBasic *PressureCor;
            PressureSIMPLE *Pressure;
            void Create(LxCFD::VelocityVector *velocityVector);
            void SetTrans(std::shared_ptr<Value1Base<double>> density);
            void CheckCreateTransRhieChow();
            virtual void Initialize() override;
            virtual void PrepareToSave() override;
            virtual void SaveOldValue(int taskIndex) override;

        protected:
            VelocityVector *VelocityVector;
            std::shared_ptr<Value1Base<double>> Density;
            void saveOldValue(IndexNumber &indexNumber, int taskIndex);
            void save0(int taskIndex);
        };

        std::vector<std::unique_ptr<NoSlipWall>> NoSlipWalls;
        std::vector<std::unique_ptr<Symmetry>> Symmetries;
        std::vector<std::unique_ptr<VelocityInlet>> VelocityInlets;
        std::vector<std::unique_ptr<PressureInOut>> PressureInOuts;
        std::shared_ptr<Value1Base<double>> UVW_Gamma;
        std::shared_ptr<ValueBase<Vector3d>> UVW_Source;
        std::shared_ptr<Value1Base<Vector3d>> UVW_IniValue;
        double UVW_RelaxFactor = 1;
        std::shared_ptr<Value1Base<double>> DynamicViscosity;
        std::shared_ptr<Value1Base<double>> Density;
        std::unique_ptr<NSEquation> U;
        std::unique_ptr<NSEquation> V;
        std::unique_ptr<NSEquation> W;
        std::unique_ptr<TransientVelocity> TransVelData;
    protected:
        std::vector<double> *U_x;
        std::vector<double> *V_x;
        std::vector<double> *W_x;
        std::vector<double> *U_bFaceCommon;
        std::shared_ptr<std::vector<double>> V_bFaceCommon;
        std::shared_ptr<std::vector<double>> W_bFaceCommon;

    public:
        Vector3d GetVelocity(int cellIndex);
        virtual void CheckCreate(FvZone &zone) override;
        void SetZone_CommonTerm(std::shared_ptr<Value1Base<double>> UVW_gamma, std::shared_ptr<Value1Base<double>> dynamicViscosity, std::shared_ptr<ValueBase<Vector3d>> UVW_source, std::shared_ptr<Value1Base<Vector3d>> UVW_iniValue, double UVW_relaxFactor);
        void SetZone_ConvTerm(std::shared_ptr<Value1Base<double>> density, ConvectionSchemes convectionSchemes);
        void SetBoundary_NoSlipMovingWall(std::shared_ptr<Value1Base<Vector3d>> boundaryVelocity, FvThread &thread);
        void SetBoundary_NoSlipStaticWall(FvThread &thread);
        void SetBoundary_SlipWall(FvThread &thread);
        void SetBound_VelocityInlet(std::shared_ptr<Value1Base<Vector3d>> value3d, FvThread &thread);
        void SetBound_VelocityInlet(std::shared_ptr<Value1Base<double>> value, FvThread &thread); //方向垂直壁面指向域内
        void SetBound_PressureInOut(std::shared_ptr<Value1Base<double>> pressure, std::shared_ptr<Value1Base<Vector3d>> direction, FvThread &thread);
        void SetBound_PressureInOut(std::shared_ptr<Value1Base<double>> pressure, FvThread &thread); //方向垂直壁面指向域内
        virtual void Initialize() override;
        void initialize(int taskIndex);
        void SetUVW_x(int taskIndex);
        void AddViscositySource_LoopFace(int taskIndex); //由于每个线程处理的index是固定的，不需要考虑同步的问题
        void AddSource_LoopCell(int taskIndex);
        void UpdateUVWBound(int taskIndex);
        virtual void CalResidual(int taskIndex) override;
        virtual void GetResidual_Reset(double &out_Rc, double &out_acPhic) override;
        virtual void CalFaceMassFlux(int taskIndex) override; //界面速度插值及massFlux计算
        void SetZone_TransTerm(bool isEnable, std::shared_ptr<Value1Base<double>> Trans, std::shared_ptr<Value1Base<double>> density);
        void SetZone_RhieChow_AfterSetTrans(PressureCorrectionBasic *pressureCorInSIMPLE, PressureSIMPLE *pressureInSIMPLE);

    protected:
        std::atomic<double> Max_Rc;
        std::atomic<double> Max_acPhic;
        std::unique_ptr<RhieChowInterpolation> VelocityInterpolation;
        void setUVW_x(Value1Base<Vector3d> &UVWValue, IndexNumber &indexNumber, int taskIndex);
        void set_x_MovingWall(Value1Base<Vector3d> &UVWValue, IndexNumber &indexNumber, int taskIndex);
        void set_x_SlipWall(IndexNumber &indexNumber, int taskIndex);
        void set_x_pressureBound(Value1Base<Vector3d> &direction, IndexNumber &indexNumber, int taskIndex);
        void Add_bSource(ValueBase<Vector3d> *S_Value3d, IndexNumber &indexNumber, int taskIndex);
        void addFaceViscositySource_inner(int taskIndex);
        void addFaceViscositySource_boundOwner(IndexNumber &indexNumber, int taskIndex);
        void addUVW_Ab_WallShearStress(IndexNumber &indexNumber, int taskIndex);
        void addUVW_Ab_NormalStress(Value1Base<double> &gamma, IndexNumber &indexNumber, int taskIndex);
        void setWallFlux0(Wall &b, int taskIndex);
        void calFaceMassFlux_VelBound(IndexNumber &indexNumber, int taskIndex);
        void calFaceMassFlux_inner(int taskIndex);
        void calFaceMassFlux_pressureBound(IndexNumber &indexNumber, int taskIndex);
        float calVelocityDirectionCorrecion(Vector3d &v_O, Vector3d &v_N, Vector3d &vf, FvFace &face, double density);
    };
}