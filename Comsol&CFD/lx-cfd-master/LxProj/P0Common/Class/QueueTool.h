#pragma once
#include <vector>
#include "ShortArray.h"
namespace LxCFD
{
    class QueueTool
    {
    public:
        struct Queue
        {
        public:
            int Length;
            int LastOne;
        };
        struct One
        {
            int PrevOneID;
        };
        std::vector<Queue> Queues;
        std::vector<One> Ones;
        void Resize(int queueLength, int oneLength);
        void Reset();
        void AddOneToQueue(int queueID, int oneID);
        void AddOnesToNewQueue(std::vector<int> &ones);
        void AddOnesToCurrentQueue(int queueID, std::vector<int> &ones);
        void ConvertQueueToArray(ShortArray::Shallow &out_Array,ShortArray::Deep &storage, int queueID);
    };
}