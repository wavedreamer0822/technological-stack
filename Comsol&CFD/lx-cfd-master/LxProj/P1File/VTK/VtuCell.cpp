#include "VtuCell.h"

namespace LxCFD
{
    bool VtuCell::AddCellInf_bound(const FvCell &fvCell, const std::vector<FvFace> &faces, ShortArray::Deep &store, int &iniOffset)
    {
        const FvFace &face = faces.at(fvCell.NFaces.at(0));
        switch (face.NodeIDs.GetLengh())
        {
        case 0:
        case 1:
        case 2:
            return false;
        case 3:
            Type = 5;
            break;
        case 4:
            Type = 9;
            break;
        default:
            Type = 7;
            break;
        }
        Connect = store.Create(face.NodeIDs);
        iniOffset += face.NodeIDs.GetLengh();
        OffSet = iniOffset;
        return true;
    }

    bool VtuCell::AddCellInf_inner(const FvCell &fvCell, const std::vector<FvFace> &faces, ShortArray::Deep &store, int &iniOffset)
    {
        int faceCount = fvCell.OFaces.GetLengh() + fvCell.NFaces.GetLengh();
        if (faceCount == 4)
        {
            Connect = store.Create(4);
            iniOffset += 4;
            OffSet = iniOffset;
            Type = 10;
            int nodeflag = 0;
            for (auto &ofid : fvCell.OFaces)
            {
                auto &fvFace = faces.at(ofid);
                if (fvFace.NodeIDs.GetLengh() != 3)
                    return false;
                if (nodeflag == 0)
                {
                    AddFirstFace_Reverse(fvFace, nodeflag);
                }
                else
                {
                    AddFace_3Nodes(fvFace, nodeflag);
                }
            }
            for (auto &nfid : fvCell.NFaces)
            {
                auto &fvFace = faces.at(nfid);
                if (fvFace.NodeIDs.GetLengh() != 3)
                    return false;
                if (nodeflag == 0)
                {
                    AddFirstFace_Forward(fvFace, nodeflag);
                }
                else
                {
                    AddFace_3Nodes(fvFace, nodeflag);
                }
            }
        }
        else if (faceCount == 6)
        {
            Connect = store.Create(8);
            iniOffset += 8;
            OffSet = iniOffset;
            Type = 12;
            int nodeflag = 0;
            for (auto &ofid : fvCell.OFaces)
            {
                auto &fvFace = faces.at(ofid);
                if (fvFace.NodeIDs.GetLengh() != 4)
                    return false;
                if (nodeflag == 0)
                {
                    AddFirstFace_Reverse(fvFace, nodeflag);
                }
                else
                {
                    AddFace_4Nodes(fvFace);
                }
            }
            for (auto &nfid : fvCell.NFaces)
            {
                auto &fvFace = faces.at(nfid);
                if (fvFace.NodeIDs.GetLengh() != 4)
                    return false;
                if (nodeflag == 0)
                {
                    AddFirstFace_Forward(fvFace, nodeflag);
                }
                else
                {
                    AddFace_4Nodes(fvFace);
                }
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    void VtuCell::AddFirstFace_Forward(const FvFace &face, int &nodeFlag)
    {
        nodeFlag = face.NodeIDs.GetLengh();
        for (int i1 = 0; i1 < nodeFlag; ++i1)
        {
            Connect[i1] = face.NodeIDs[i1];
        }
    }
    void VtuCell::AddFirstFace_Reverse(const FvFace &face, int &nodeFlag)
    {
        nodeFlag = face.NodeIDs.GetLengh();
        for (int i1 = 0; i1 < nodeFlag; ++i1)
        {
            Connect[i1] = face.NodeIDs[nodeFlag - i1 - 1];
        }
    }
    void VtuCell::AddFace_3Nodes(const FvFace &face, int &nodeFlag)
    {
        if (nodeFlag == 4)
            return;
        for (auto &nid : face.NodeIDs)
        {
            if (nid != Connect[0] && nid != Connect[1] && nid != Connect[2])
            {
                Connect[3] = nid;
                nodeFlag = 4;
                return;
            }
        }
    }
    void VtuCell::AddFace_4Nodes(const FvFace &face)
    {
        int lastOne = InConnect(face.NodeIDs.at(0));
        for (int i1 = 1; i1 < 4; ++i1)
        {
            int thisOne = InConnect(face.NodeIDs.at(i1));
            if (lastOne < 0 && thisOne >= 0)
            {
                Connect.at(thisOne + 4) = face.NodeIDs.at(i1 - 1);
            }
            else if (lastOne >= 0 && thisOne < 0)
            {
                Connect.at(lastOne + 4) = face.NodeIDs.at(i1);
            }
            lastOne = thisOne;
        }
        {
            int thisOne = InConnect(face.NodeIDs.at(0));
            if (lastOne < 0 && thisOne >= 0)
            {
                Connect.at(thisOne + 4) = face.NodeIDs.at(3);
            }
            else if (lastOne >= 0 && thisOne < 0)
            {
                Connect.at(lastOne + 4) = face.NodeIDs.at(0);
            }
        }
    }
    int VtuCell::InConnect(int nodeID)
    {
        for (int i2 = 0; i2 < 4; ++i2)
        {
            if (nodeID == Connect.at(i2))
            {
                return i2;
            }
        }
        return -1;
    }

}