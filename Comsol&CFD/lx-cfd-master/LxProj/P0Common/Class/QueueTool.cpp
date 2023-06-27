#include "QueueTool.h"

namespace LxCFD
{
    void QueueTool::Resize(int queueLength, int oneLength)
    {
        Queues.resize(queueLength);
        Ones.resize(oneLength);
        Reset();
    }

    void QueueTool::Reset()
    {
        for (auto &q : Queues)
        {
            q.Length = 0;
        }
    }

    void QueueTool::AddOneToQueue(int queueID, int oneID)
    {
        Queue &q = Queues.at(queueID);
        if (q.Length == 0)
        {
            q.LastOne = oneID;
        }
        else
        {
            Ones.at(oneID).PrevOneID = q.LastOne;
            q.LastOne = oneID;
        }
        ++q.Length;
    }
    void QueueTool::AddOnesToNewQueue(std::vector<int> &ones)
    {
        Queues.push_back(Queue());
        Queue &q = Queues.back();
        q.Length = ones.size();
        int prevOne = -1;
        for (auto &one : ones)
        {
            Ones.at(one).PrevOneID = prevOne;
            prevOne = one;
        }
        q.LastOne = prevOne;
    }
    void QueueTool::AddOnesToCurrentQueue(int queueID, std::vector<int> &ones)
    {
        Queue &q = Queues.at(queueID);
        q.Length += ones.size();
        int prevOne = q.LastOne;
        for (auto &one : ones)
        {
            Ones.at(one).PrevOneID = prevOne;
            prevOne = one;
        }
        q.LastOne = prevOne;
    }
    void QueueTool::ConvertQueueToArray(ShortArray::Shallow &out_Array, ShortArray::Deep &storage, int queueID)
    {
        Queue &q = Queues.at(queueID);
        out_Array = storage.Create(q.Length);
        int prevOne = q.LastOne;
        for (int pos = q.Length - 1; pos >= 0; --pos)
        {
            out_Array.at(pos) = prevOne;
            prevOne = Ones.at(prevOne).PrevOneID;
        }
    }
}
// for (int i1 = 0; i1 < Queues.size(); ++i1)
// {
//     Queues[i1].Length = 0;
// }