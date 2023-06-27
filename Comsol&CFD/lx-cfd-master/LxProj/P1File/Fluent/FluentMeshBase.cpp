#include "FluentMeshBase.h"
#include "AppRes.h"
#include "LxString.h"
namespace LxCFD
{
	void FluentMeshBase::FlHead::SetHead(const std::vector<std::string>& splitedStrings)
	{
		ID = std::stoi(splitedStrings.at(1), 0, 16);
		Index.Start = std::stoi(splitedStrings.at(2), 0, 16) - 1;
		Index.End = std::stoi(splitedStrings.at(3), 0, 16) - 1;
	}
	// void FluentMeshBase::Face::Set(ShallowArrayStorage &store, const std::vector<std::string> &ss)
	// {
	//     Nodes.Create(store, ss.size() - 2); // = std::vector<int>(ss.size() - 2);
	//     std::size_t i1 = 0;
	//     for (; i1 < Nodes.GetLengh(); ++i1)
	//     {
	//         Nodes[i1] = std::stoi(ss.at(i1), 0, 16) - 1;
	//     }
	//     c0 = std::stoi(ss.at(i1), 0, 16) - 1;
	//     c1 = std::stoi(ss.at(i1 + 1), 0, 16) - 1;
	// }
	//void FluentMeshBase::FlZone::AddThread(FlThread *flThread, FThreadTypes fThreadType)
	//{
	//    Threads.push_back(flThread);
	//    ThreadsType.push_back(fThreadType);
	//}
	//void FluentMeshBase::FlZone::AddToFvZone(FvMesh &fvmesh)
	//{
	//    std::unique_ptr<FvZone> fvzone(new FvZone());
	//    fvzone->Name = Name;
	//    fvzone->ID = ID;
	//    int faceflag = 0;
	//    for (auto &ft : Threads)
	//    {
	//        faceflag += ft->Faces.size();
	//    }
	//    std::vector<FvFace> &fvfaces = fvzone->Faces;
	//    fvfaces.resize(faceflag);
	//    auto &store = fvzone->ShallowArrayStorage;
	//    store.Initialize(1,faceflag);
	//    int first_index = Index.Start;
	//    faceflag = 0;
	//    //先查找添加interior
	//    for (std::size_t i2 = 0; i2 < Threads.size(); i2++)
	//    {
	//        if (ThreadsType.at(i2) == FThreadTypes::interior)
	//        {
	//            for (auto &ff : Threads.at(i2)->Faces)
	//            {
	//                fvfaces.at(faceflag).Set(store, ff.Nodes, ff.c0 - first_index, ff.c1 - first_index, false);
	//                faceflag++;
	//            }
	//        }
	//    }
	//    fvzone->InnerIndex = IndexNumber(0, Index.GetCount() - 1, 0, faceflag - 1);
	//    int deltacellfacecount = fvzone->InnerIndex.CellIDs.End - fvzone->InnerIndex.FaceIDs.End;
	//    //后查找添加interior之外的
	//    for (std::size_t i2 = 0; i2 < Threads.size(); i2++)
	//    {
	//        if (ThreadsType.at(i2) == FThreadTypes::interior)
	//            continue;
	//        std::unique_ptr<FvThread> fvthread(new FvThread(fvzone.get()));
	//        fvthread->Name = Threads.at(i2)->Name;
	//        fvthread->ID = Threads.at(i2)->ID;

	//        int startFaceID = faceflag;
	//        //把thread中的face全部添加到mesh zone中的faces
	//        switch (ThreadsType.at(i2))
	//        {
	//        case FThreadTypes::boundary:
	//            for (auto &ff : Threads.at(i2)->Faces)
	//            {
	//                fvfaces.at(faceflag).Set(store, ff.Nodes, ff.c0 - first_index, faceflag + deltacellfacecount, false);
	//                faceflag++;
	//            }
	//            break;
	//        case FThreadTypes::interface_c0:
	//            for (auto &ff : Threads.at(i2)->Faces)
	//            {
	//                fvfaces.at(faceflag).Set(store, ff.Nodes, ff.c0 - first_index, faceflag + deltacellfacecount, false);
	//                faceflag++;
	//            }
	//            fvthread->RootContact = Threads.at(i2)->RootContact;
	//            fvthread->RootContact->OZone = fvzone.get();
	//            fvthread->RootContact->OThread = fvthread.get();
	//            break;
	//        case FThreadTypes::interface_c1:
	//            for (auto &ff : Threads.at(i2)->Faces)
	//            {
	//                fvfaces.at(faceflag).Set(store, ff.Nodes, ff.c1 - first_index, faceflag + deltacellfacecount, true);
	//                faceflag++;
	//            }
	//            fvthread->RootContact = Threads.at(i2)->RootContact;
	//            fvthread->RootContact->NZone = fvzone.get();
	//            fvthread->RootContact->NThread = fvthread.get();
	//            break;
	//        default:
	//            break;
	//        }
	//        int endFaceID = faceflag - 1;
	//        fvthread->ThreadIndex = IndexNumber(startFaceID + deltacellfacecount, endFaceID + deltacellfacecount, startFaceID, endFaceID);
	//        fvzone->BoundThreads.push_back(std::move(fvthread));
	//    }
	//    int totalEndFaceID = faceflag - 1;
	//    fvzone->TotalIndex = IndexNumber(0, totalEndFaceID + deltacellfacecount, 0, totalEndFaceID);
	//    fvmesh.Zones.push_back(std::move(fvzone));
	//}

	//void FluentMeshBase::ConvertToMesh()
	//{
	//    LxConsole::Info("开始网格转换……");
	//    std::unique_ptr<FvMesh> fvmesh = std::unique_ptr<FvMesh>(new FvMesh());
	//    RemarkID();
	//    DistributeThreadsToFlZone(*fvmesh);
	//    for (auto &z : FlZones)
	//    {
	//        z->AddToFvZone(*fvmesh);
	//    }
	//    DistributeNodesToFvZone(*fvmesh);
	//    AppRes::FvMesh = std::move(fvmesh);
	//    LxConsole::Info("完成网格转换。");
	//}
	//void FluentMeshBase::RemarkID()
	//{
	//    for (std::size_t i1 = 0; i1 < FlZones.size(); ++i1)
	//    {
	//        FlZones.at(i1)->ID = i1;
	//    }
	//    for (std::size_t i1 = 0; i1 < FlThreads.size(); ++i1)
	//    {
	//        FlThreads.at(i1)->ID = i1;
	//    }
	//}
	//int FluentMeshBase::FindZoneByCell(int cellID)
	//{
	//    for (std::size_t i1 = 0; i1 < FlZones.size(); ++i1)
	//    {
	//        auto &z = *FlZones.at(i1);
	//        if (cellID >= z.Index.Start && cellID <= z.Index.End)
	//        {
	//            return z.ID;
	//        }
	//    }
	//    return -1;
	//}
	//void FluentMeshBase::DistributeThreadsToFlZone(FvMesh &fvmesh)
	//{
	//    for (std::size_t i1 = 0; i1 < FlThreads.size(); ++i1)
	//    {
	//        FlThread &thread = *FlThreads.at(i1);
	//        int oZone = FindZoneByCell(thread.Faces.at(0).c0);
	//        int c1Flag = thread.Faces.at(0).c1;
	//        if (c1Flag < 0)
	//        {
	//            FlZones.at(oZone)->AddThread(&thread, FThreadTypes::boundary);
	//        }
	//        else
	//        {
	//            int nZone = FindZoneByCell(c1Flag);
	//            if (nZone == oZone)
	//            {
	//                FlZones.at(oZone)->AddThread(&thread, FThreadTypes::interior);
	//            }
	//            else
	//            {
	//                FlZones.at(oZone)->AddThread(&thread, FThreadTypes::interface_c0);
	//                FlZones.at(nZone)->AddThread(&thread, FThreadTypes::interface_c1);
	//                std::unique_ptr<FvContact> fvcontact = std::unique_ptr<FvContact>(new FvContact());
	//                fvcontact->Name = thread.Name,
	//                fvcontact->IsConode = true;
	//                thread.RootContact = fvcontact.get();
	//                fvmesh.Contacts.push_back(std::move(fvcontact));
	//            }
	//        }
	//    }
	//}

	//void FluentMeshBase::DistributeNodesToFvZone(FvMesh &fvmesh)
	//{
	//    std::vector<int> nodeNewIndex(FlNodes.size());
	//    for (auto &fvz : fvmesh.Zones)
	//    {
	//        for (std::size_t i1 = 0; i1 < nodeNewIndex.size(); ++i1)
	//        {
	//            nodeNewIndex[i1] = -1;
	//        }
	//        auto &fvnodes = fvz->Nodes;
	//        fvnodes.clear();
	//        fvnodes.reserve(FlNodes.size());
	//        for (auto &fvf : fvz->Faces)
	//        {
	//            for (int i3 = 0; i3 < fvf.NodeIDs.GetLengh(); ++i3)
	//            {
	//                int oldIndex = fvf.NodeIDs.at(i3);
	//                if (nodeNewIndex.at(oldIndex) < 0)
	//                {
	//                    nodeNewIndex.at(oldIndex) = fvnodes.size();
	//                    fvf.NodeIDs.at(i3) = fvnodes.size();
	//                    fvnodes.push_back(FlNodes.at(oldIndex));
	//                }
	//                else
	//                {
	//                    fvf.NodeIDs.at(i3) = nodeNewIndex.at(oldIndex);
	//                }
	//            }
	//        }
	//        fvnodes.shrink_to_fit();
	//    }
	//}



	void FluentMeshBase::ConvertToMesh()
	{
		std::unique_ptr< FvMesh> mesh = std::make_unique<FvMesh>();
		RemarkID();
		Evalue();
		Distrubute(*mesh);
		AppRes::FvMesh = std::move(mesh);
		AppRes::FvMesh->PrepareMeshData();
	}
	void FluentMeshBase::RemarkID()
	{
		for (size_t i1 = 0; i1 < FlZones.size(); i1++)
		{
			FlZones[i1]->ID = i1;
		}
		for (size_t i1 = 0; i1 < FlThreads.size(); i1++)
		{
			FlThreads[i1]->ID = i1;
		}
	}
	FluentMeshBase::FlZone* FluentMeshBase::FindZoneByCell(int cellID)
	{
		for (auto& z : FlZones)
		{
			if (cellID >= z->Index.Start && cellID <= z->Index.End)
			{
				return z.get();
			}
		}
		return nullptr;
	}
	void FluentMeshBase::Evalue()
	{
		for (auto& z : FlZones)
		{
			z->FvFaceCount = 0;
		}
		for (auto& t : FlThreads)
		{
			if (isThreadInterior(*t))
			{
				FlZone* z = FindZoneByCell(t->Faces[0].c0);
				z->FvFaceCount += t->Faces.size();
				continue;
			}
			FlZone* z0 = nullptr, * z1 = nullptr;
			auto& flFaces = t->Faces;
			for (int i1 = 0; i1 < flFaces.size(); i1++)
			{
				auto& f = flFaces[i1];
				if (isCellInZone(f.c0, z0) && isCellInZone(f.c1, z1))
				{
					flagFlFaceWithZone(f, z0, z1);
				}
				else
				{
					z0 = FindZoneByCell(f.c0);
					z1 = FindZoneByCell(f.c1);
					t->AddSplitThread(z0, z1);
					flagFlFaceWithZone(f, z0, z1);
				}
			}
		}
	}
	void FluentMeshBase::Distrubute(FvMesh& fvMesh)
	{
		for (auto& z : FlZones)
		{
			std::unique_ptr<FvZone> fvz = std::make_unique<FvZone>();
			fvz->Name = z->Name;
			fvz->ID = z->ID;
			fvz->Faces.resize(z->FvFaceCount);// new FvFace[z->FvFaceCount],
			fvz->ShallowArrayStorage.Initialize(1, z->FvFaceCount);
			fvz->Nodes = FlNodes;
			fvMesh.Zones.push_back(std::move(fvz));
			z->FvFaceCount = 0;
		}
		for (auto& t : FlThreads)
		{
			if (isThreadInterior(*t))
			{
				FlZone* z = FindZoneByCell(t->Faces[0].c0);
				FvZone* fvz = fvMesh.Zones[z->ID].get();
				for (auto& ff : t->Faces)
				{
					fvz->Faces[z->FvFaceCount].Set(fvz->ShallowArrayStorage, ff.Nodes, ff.c0 - z->Index.Start, ff.c1 - z->Index.Start, false);
					z->FvFaceCount++;
				}
			}
		}
		for (int i1 = 0; i1 < FlZones.size(); i1++)
		{
			fvMesh.Zones[i1]->InnerIndex = IndexNumber(0, FlZones[i1]->Index.GetCount() - 1, 0, FlZones[i1]->FvFaceCount - 1);
		}
		for (auto& t : FlThreads)
		{
			if (isThreadInterior(*t)) continue;
			for (auto& st : t->SplitThreads)
			{
				if (st.z1 == -1)
				{
					FlZone* z0 = FlZones[st.z0].get();
					FvZone* fvz0 = fvMesh.Zones[st.z0].get();
					int cellstart, facestart;
					GetLastIndexNumber(*fvz0, cellstart, facestart);
					int celllog = cellstart;
					for (auto& ff : t->Faces)
					{
						if (st.z0 == ff.z0)
						{
							fvz0->Faces[z0->FvFaceCount].Set(fvz0->ShallowArrayStorage, ff.Nodes, ff.c0 - z0->Index.Start, celllog, false);
							z0->FvFaceCount++;
							celllog++;
						}
					}
					AddThread(fvz0, *t, IndexNumber(cellstart, cellstart + z0->FvFaceCount - facestart - 1, facestart, z0->FvFaceCount - 1));
				}
				else
				{
					FlZone* z0 = FlZones[st.z0].get(), * z1 = FlZones[st.z1].get();
					FvZone* fvz0 = fvMesh.Zones[st.z0].get(), * fvz1 = fvMesh.Zones[st.z1].get();
					int z0cellstart, z0facestart;
					int z1cellstart, z1facestart;
					GetLastIndexNumber(*fvz0, z0cellstart, z0facestart);
					GetLastIndexNumber(*fvz1, z1cellstart, z1facestart);
					int z0celllog = z0cellstart, z1celllog = z1cellstart;
					for (auto& ff : t->Faces)
					{
						if (st.z0 == ff.z0 && st.z1 == ff.z1)
						{
							fvz0->Faces[z0->FvFaceCount].Set(fvz0->ShallowArrayStorage, ff.Nodes, ff.c0 - z0->Index.Start, z0celllog, false);
							z0->FvFaceCount++;
							z0celllog++;
							fvz1->Faces[z1->FvFaceCount].Set(fvz1->ShallowArrayStorage, ff.Nodes, ff.c1 - z1->Index.Start, z1celllog, true);
							z1->FvFaceCount++;
							z1celllog++;
						}
					}
					FvThread* ot = AddThread(fvz0, *t, IndexNumber(z0cellstart, z0cellstart + z0->FvFaceCount - z0facestart - 1, z0facestart, z0->FvFaceCount - 1));
					FvThread* nt = AddThread(fvz1, *t, IndexNumber(z1cellstart, z1cellstart + z1->FvFaceCount - z1facestart - 1, z1facestart, z1->FvFaceCount - 1));
					std::unique_ptr< FvContact> fc = std::make_unique< FvContact>();
					fc->Name = t->Name;
					fc->IsConode = true;
					fc->OZone = fvz0;
					fc->NZone = fvz1;
					fc->OThread = ot;
					fc->NThread = nt;
					fvMesh.Contacts.push_back(std::move(fc));
					ot->RootContact = fc.get();
					nt->RootContact = fc.get();
				}
			}
		}
		for (auto& z : fvMesh.Zones)
		{
			int cl, fl;
			GetLastIndexNumber(*z, cl, fl);
			z->TotalIndex = IndexNumber(0, cl - 1, 0, fl - 1);
		}
	}
	FvThread* FluentMeshBase::AddThread(FvZone* z, FlThread& t, IndexNumber id)
	{
		std::unique_ptr<FvThread> b(new FvThread(z));
		b->Name = t.Name;
		b->ID = t.ID;
		b->ThreadIndex = id;
		z->BoundThreads.push_back(std::move(b));
		return z->BoundThreads[z->BoundThreads.size() - 1].get();
	}
	void FluentMeshBase::GetLastIndexNumber(FvZone& z, int& cellLenth, int& faceLenth)
	{
		IndexNumber num = z.BoundThreads.size() == 0 ? z.InnerIndex : z.BoundThreads[z.BoundThreads.size() - 1]->ThreadIndex;
		cellLenth = num.CellIDs.End + 1;
		faceLenth = num.FaceIDs.End + 1;
	}
	void FluentMeshBase::flagFlFaceWithZone(FlFace& f, FlZone* z0, FlZone* z1)
	{
		f.z0 = z0->ID;
		z0->FvFaceCount++;
		if (z1 != nullptr)
		{
			f.z1 = z1->ID;
			z1->FvFaceCount++;
		}
	}
	bool FluentMeshBase::isThreadInterior(FlThread& t)
	{
		return LxString::StartWith(t.Name, "int_") && t.FlType == "interior";
	}
	bool FluentMeshBase::isCellInZone(int cellID, FlZone* z)
	{
		if (z == nullptr)
		{
			return cellID == -1;
		}
		return cellID >= z->Index.Start && cellID <= z->Index.End;
	}



}