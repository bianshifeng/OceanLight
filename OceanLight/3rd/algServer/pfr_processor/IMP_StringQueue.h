#ifndef IMP_STRINGQUEUE_H
#define IMP_STRINGQUEUE_H

#include <QString>
#include "common/IMP_Lock.h"
#include <QDebug>
#include "common/imp_algo_type.h"
#include "IMP_pfr_path.h"

#define DEFAULT_MAX_QUEUE_SIZE		15



class IMP_StringQueue
{
public:
    IMP_StringQueue();
    explicit IMP_StringQueue(int maxQueueSize);
    ~IMP_StringQueue();
    int InitQueue();
    int GetQueueLen();
    int IsEmpty();
    int IsFull();
    IMP_PFR_PATH* GetFrameAddr();

    int Peek(IMP_PFR_PATH** pString);
    int EndPeek();
    int Remove();

    int ClearQueue();

    IMP_PFR_PATH* FindMatchAddr(int nFrameNo);

private:
    IMP_CriticalSection m_queueLock;
    IMP_PFR_PATH *m_pArray;

    volatile int m_peekFlag;	//1:peeking using		0:not used
    volatile int m_queueHead;
    volatile int m_queueTail;

    int m_queueMaxSize;		//队列的最大长度
    int m_nQueueLen;

};
#endif // IMP_STRINGQUEUE_H
