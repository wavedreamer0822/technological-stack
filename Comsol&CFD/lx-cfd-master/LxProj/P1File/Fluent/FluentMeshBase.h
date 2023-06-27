#pragma once
#include <vector>
#include "FvMesh.h"
#include "ShortArray.h"
namespace LxCFD
{
	class FluentMeshBase
	{
	public:
		struct FlFace
		{
		public:
			ShortArray::Shallow Nodes;
			int c0;
			int c1;
			int z0;
			int z1;
		};
		class FlHead : public HeadBase
		{
		public:
			IndexRecorder Index;
			std::string FlType;
			void SetHead(const std::vector<std::string>& splitedStrings);
		};

		class FlZone : public FlHead
		{
		public:
			std::unique_ptr<std::vector<FvFace>> FvFaces;
			int FvFaceCount = 0;
		};
		class FlThread : public FlHead
		{
		public:
			struct SplitThread
			{
			public:
				int z0;
				int z1;
			};
			std::vector<FlFace> Faces;
			FvContact* RootContact;
			std::vector<SplitThread> SplitThreads;
			void AddSplitThread(FlZone* z0, FlZone* z1)
			{
				int z0id = z0->ID;
				int z1id = z1 == nullptr ? -1 : z1->ID;
				for (auto& st : SplitThreads)
				{
					if (st.z0 == z0id && st.z1 == z1id)
					{
						return;
					}
				}
				SplitThread sp = SplitThread();
				sp.z0 = z0id;
				sp.z1 = z1id;
				SplitThreads.push_back(sp);
			}

		};

		std::shared_ptr<std::vector<Vector3d>> FlNodes{ new std::vector<Vector3d>() };
		std::vector<std::unique_ptr<FlZone>> FlZones;
		std::vector<std::unique_ptr<FlThread>> FlThreads;
		ShortArray::Deep ShallowArrayStorage;
	protected:
		void ConvertToMesh();
		void RemarkID();
		FlZone* FindZoneByCell(int cellID);
		void Evalue();
		void Distrubute(FvMesh& fvMesh);
		FvThread* AddThread(FvZone* z, FlThread &t, IndexNumber id);
		void GetLastIndexNumber(FvZone& z, int& cellLenth, int& faceLenth);
		void flagFlFaceWithZone(FlFace& f, FlZone* z0, FlZone* z1);
		bool isThreadInterior(FlThread& t);
		bool isCellInZone(int cellID, FlZone* z);

	};
}