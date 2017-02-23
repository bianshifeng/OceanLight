#ifndef  __IMP_ALGO_RES_QUEUE_H__
#define  __IMP_ALGO_RES_QUEUE_H__

#include "IMP_Lock.h"
#include "IMP_AlgoRes.h"

#define DEFAULT_MAX_QUEUE_SIZE              500
#define DEFAULT_MALLOC_RES_BUF_SIZE         200000 ////1000

class IMP_AlgoResQueue
{
public:
    IMP_AlgoResQueue();
    explicit IMP_AlgoResQueue(int maxQueueSize, int nMallocResBufLen);
    ~IMP_AlgoResQueue();

    int InitQueue();
	
    int GetQueueLen();

	int IsEmpty();
	int IsFull();

    IMP_AlgoRes* GetAlgoResAddr();
	
    IMP_AlgoRes* PeekAlgoRes();
	int EndPeek();
    int RemoveAlgoRes();

	int ClearQueue();

private:
	IMP_CriticalSection m_queueLock;
    IMP_AlgoRes*       m_pAlgoResArray;

	volatile int m_peekFlag;	//1:peeking using		0:not used
	volatile int m_queueHead;
	volatile int m_queueTail;		
	
	int m_queueMaxSize;		//队列的最大长度
    int m_nMallocResBufLen;
    int m_nQueueLen;

};

#endif
