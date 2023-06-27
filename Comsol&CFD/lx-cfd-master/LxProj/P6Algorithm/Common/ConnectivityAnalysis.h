#pragma once
#include <vector>
#include "FvMesh.h"
namespace LxCFD
{
    class ConnectivityAnalysis
    {
    public:
        class ZoneMirror
        {
        public:
            int PoolID;      //-2表示无该区域，-1表示有该区域暂时没分配到pool
            int IndexInList; //在传入的list中的位置
            std::vector<int> LinkedZoneID_Bigger;
        };
        template <typename T1, typename T2>
        class ConnectedZones
        {
        public:
            std::vector<T1*> Zones;
            std::vector<T2*> Contacts;
        };
        std::vector<ZoneMirror> ZonesMirror;
        void LoadMeshInf(FvMesh &mesh)
        {
            ZonesMirror.resize(mesh.Zones.size());
        }
        template <typename T1, typename T2>
        std::vector<ConnectedZones<T1, T2>> SplitByConnectivity(std::vector<T1*>& zones, std::vector<T2*>& contacts)
        {
            reset();
            addRelationShip(zones, contacts);
            std::vector<ConnectedZones<T1, T2>> list;
            //zone
            for (auto &zoneM : ZonesMirror) //遍历zoneMirror更能保证从小到大遍历
            {
                if (zoneM.PoolID == -2)
                    continue;
                if (zoneM.PoolID == -1)
                {
                    zoneM.PoolID = list.size();
                    ConnectedZones<T1, T2> connectedDomain;
                    connectedDomain.Zones.push_back(zones.at(zoneM.IndexInList));
                    list.push_back(connectedDomain);
                }
                else
                {
                    list.at(zoneM.PoolID).Zones.push_back(zones.at(zoneM.IndexInList));
                }
                for (auto &zb : zoneM.LinkedZoneID_Bigger)
                {
                    ZonesMirror.at(zb).PoolID = zoneM.PoolID;
                }
            }
            //contact
            for (size_t i1 = 0; i1 < contacts.size(); ++i1)
            {
                int OID, NID;
                contacts.at(i1)->GetONZoneID(OID, NID);
                int inPoolID = ZonesMirror.at(OID).PoolID;
                list.at(inPoolID).Contacts.push_back(contacts.at(i1));
            }
            return list;
        }

    protected:
        void reset()
        {
            for (auto &i : ZonesMirror)
            {
                i.PoolID = -2;
                i.LinkedZoneID_Bigger.clear();
            }
        }
        template <typename T1, typename T2>
        void addRelationShip(std::vector<T1*> &zones, std::vector<T2*> &contacts)
        {
            for (size_t i1 = 0; i1 < zones.size(); ++i1)
            {
                int zoneID = zones.at(i1)->GetZoneID();
                ZonesMirror.at(zoneID).PoolID = -1;
                ZonesMirror.at(zoneID).IndexInList = i1;
            }
            for (auto &c : contacts)
            {
                int smallIDZone, bigIDZone;
                c->GetONZoneID(smallIDZone, bigIDZone);
                if (smallIDZone > bigIDZone)
                {
                    int temp = smallIDZone;
                    smallIDZone = bigIDZone;
                    bigIDZone = temp;
                }
                ZonesMirror.at(smallIDZone).LinkedZoneID_Bigger.push_back(bigIDZone);
            }
        }
    };
}