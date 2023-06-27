#include "MGContactCreator.h"

namespace LxCFD
{
	std::unique_ptr<MGContact> MGContactCreator::CreateMGContact(IProvideContactTopology* fineContact, MGZone* OZone, MGZone* NZone, IndexNumber* OIndex, IndexNumber* NIndex)
	{
		this->fineContact = fineContact;
		int count = fineContact->GetInnerIndex().FaceIDs.GetCount();
		InOCoarseCell.resize(count);
		InNCoarseCell.resize(count);
		LinkArray_Int.Initialize(5, count);
		LinkArray_MGFaceTemp.Initialize(5, count);
		for (int i1 = 0; i1 < count; ++i1)
		{
			InOCoarseCell[i1] = -1;
			InNCoarseCell[i1] = -1; //防止出错了不知道
		}
		std::unique_ptr<MGContact> mgContact = std::unique_ptr<MGContact>(new MGContact());
		coarseContact = mgContact.get();
		coarseContact->ShallowArrayStorage.Initialize(1, count);
		coarseContact->O_Zone = OZone;
		coarseContact->N_Zone = NZone;
		coarseContact->O_Cells = &OZone->Cells;
		coarseContact->N_Cells = &NZone->Cells;
		coarseContact->O_Faces = &OZone->Faces;
		coarseContact->N_Faces = &NZone->Faces;
		coarseContact->O_Index = OIndex;
		coarseContact->N_Index = NIndex;
		makeFlag();
		addContactFaceToStorage();
		splitContactCoarseFaceFromStorage();
		//checkTopology();
		contactTempCells->clear();
		return std::move(mgContact);
	}
	void MGContactCreator::makeFlag()
	{
		IndexRecorder oCellIDs = coarseContact->O_Index->CellIDs;
		IndexRecorder nCellIDs = coarseContact->N_Index->CellIDs;
		contactTempCells->resize(oCellIDs.GetCount());
		tempCellsStart = oCellIDs.Start;
		for (int i1 = oCellIDs.Start; i1 <= oCellIDs.End; ++i1)
		{
			for (auto& c : coarseContact->O_Cells->at(i1).FineCells)
			{
				for (auto& ffid : fineContact->GetOZoneCellOFaces(c))
				{
					InOCoarseCell[ffid] = i1;
				}
			}
		}
		for (int i1 = nCellIDs.Start; i1 <= nCellIDs.End; ++i1)
		{
			for (auto& c : coarseContact->N_Cells->at(i1).FineCells)
			{
				for (auto& ffid : fineContact->GetNZoneCellOFaces(c))
				{
					InNCoarseCell[ffid] = i1;
				}
			}
		}
	}

	void MGContactCreator::addContactFaceToStorage()
	{
		IndexRecorder faceIDs = fineContact->GetInnerIndex().FaceIDs;
		for (int i1 = faceIDs.Start; i1 <= faceIDs.End; ++i1)
		{
			ONPair onnew = ONPair(InOCoarseCell[i1], InNCoarseCell[i1]);
			add(i1, onnew);
		}
	}
	void MGContactCreator::add(int i1, ONPair onnew)
	{
		auto& store = contactTempCells->at(onnew.Owner - tempCellsStart).CoarseOFacesStorage;
		for (auto& f : store)
		{
			if (f.NeighborCellIndex == onnew.Neighbor)
			{
				LinkArray_Int.CreateAdd(f.FineFace_O2N, i1);
				return;
			}
		}
		LinkArray_MGFaceTemp.CreateAdd(store, MGFaceTemp());
		MGFaceTemp& cfnew = (*store.Last).Value;
		cfnew.OwnerCellIndex = onnew.Owner;
		cfnew.NeighborCellIndex = onnew.Neighbor;
		LinkArray_Int.CreateAdd(cfnew.FineFace_O2N, i1);
	}

	void MGContactCreator::splitContactCoarseFaceFromStorage()
	{
		auto& contactDeep = coarseContact->ShallowArrayStorage;
		int icount = 0;
		for (auto& c : *contactTempCells)
		{
			icount += c.CoarseOFacesStorage.Length;
		}
		auto& Pairs = coarseContact->Pairs;
		Pairs.resize(icount);

		IndexRecorder oCellIDs = coarseContact->O_Index->CellIDs;
		IndexRecorder nCellIDs = coarseContact->N_Index->CellIDs;
		IndexRecorder oFaceIDs = coarseContact->O_Index->FaceIDs;
		IndexRecorder nFaceIDs = coarseContact->N_Index->FaceIDs;
		auto& oFaces = *coarseContact->O_Faces;
		auto& nFaces = *coarseContact->N_Faces;

		QueueTool_O.Resize(oCellIDs.GetCount(), Pairs.size());
		QueueTool_N.Resize(nCellIDs.GetCount(), Pairs.size());
		{
			int i1 = 0;
			for (auto& c : *contactTempCells)
			{
				for (auto& f : c.CoarseOFacesStorage)
				{
					MGPair& pair = Pairs.at(i1);
					pair.FinePairs = contactDeep.Create(f.FineFace_O2N);
					pair.O_Cell = f.OwnerCellIndex;
					pair.O_Face = f.OwnerCellIndex + oFaceIDs.Start - oCellIDs.Start;
					pair.O_InnCell = oFaces[pair.O_Face].OSideCell;
					pair.N_Cell = f.NeighborCellIndex;
					pair.N_Face = f.NeighborCellIndex + nFaceIDs.Start - nCellIDs.Start;
					pair.N_InnCell = nFaces[pair.N_Face].OSideCell;
					QueueTool_O.AddOneToQueue(f.OwnerCellIndex - oCellIDs.Start, i1);
					QueueTool_N.AddOneToQueue(f.NeighborCellIndex - nCellIDs.Start, i1);
					++i1;
				}
			}
		}
		auto& ocells = *coarseContact->O_Cells;
		for (int i1 = oCellIDs.Start; i1 <= oCellIDs.End; ++i1)
		{
			QueueTool_O.ConvertQueueToArray(ocells.at(i1).OFaces, contactDeep, i1 - oCellIDs.Start);
		}
		auto& ncells = *coarseContact->N_Cells;
		for (int i1 = nCellIDs.Start; i1 <= nCellIDs.End; ++i1)
		{
			QueueTool_N.ConvertQueueToArray(ncells.at(i1).OFaces, contactDeep, i1 - nCellIDs.Start);
		}
		coarseContact->InnerIndex = IndexNumber(0, Pairs.size() - 1, 0, Pairs.size() - 1);
	}

	void MGContactCreator::checkTopology()
	{
		auto& pairs = coarseContact->Pairs;
		int indexcount = fineContact->GetInnerIndex().FaceIDs.GetCount();
		int finecount = 0;
		for (auto& f : pairs)
		{
			finecount += f.FinePairs.GetLengh();
		}
		if (indexcount != finecount)
		{
			LxConsole::Error("Contact网格数量不一致");
		}
		for (int i1 = coarseContact->O_Index->CellIDs.Start; i1 <= coarseContact->O_Index->CellIDs.End; ++i1)
		{
			auto& faces = coarseContact->O_Cells->at(i1).OFaces;
			for (auto& pid : faces)
			{
				if (pairs.at(pid).O_Cell != i1)
				{
					LxConsole::Error("生成粗网格交界面出错1");
				}

				if (pairs.at(pid).O_Face != coarseContact->O_Cells->at(i1).NFaces[0])
				{
					LxConsole::Error("生成粗网格交界面出错2"); //,cell{i1},pair中ID{pairs[pid].O_Face}Cell中ID{coarseContact.O_Cells[i1].NFaces[0]}
					// printFace(pairs[pid].O_Face);
					// printFace(coarseContact.O_Cells[i1].NFaces[0]);
					// void printFace(int faceid)
					// {
					//     Console.WriteLine($ "{faceid} face ,owner {coarseContact.O_Faces[faceid].OSideCell}, neighbor{coarseContact.O_Faces[faceid].NSideCell}");
					// }
				}
			}
		}
		for (int i1 = coarseContact->N_Index->CellIDs.Start; i1 <= coarseContact->N_Index->CellIDs.End; ++i1)
		{
			for (auto& pid : coarseContact->N_Cells->at(i1).OFaces)
			{
				if (pairs.at(pid).N_Cell != i1)
				{
					LxConsole::Error("生成粗网格交界面出错3");
				}

				if (pairs.at(pid).N_Face != coarseContact->N_Cells->at(i1).NFaces[0])
				{
					LxConsole::Error("生成粗网格交界面出错4");
				}
			}
		}
	}
}