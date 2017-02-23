#include "QDebug"
#include "IMP_AlgoResQueue.h"
#include "imp_algo_type.h"

IMP_AlgoResQueue::IMP_AlgoResQueue():m_nQueueLen(0), m_peekFlag(0), m_queueHead(0), m_queueTail(0), m_queueMaxSize(DEFAULT_MAX_QUEUE_SIZE),
m_nMallocResBufLen(DEFAULT_MALLOC_RES_BUF_SIZE)
{

}



IMP_AlgoResQueue::IMP_AlgoResQueue(int maxQueueSize, int nMallocResBufLen):m_nQueueLen(0), m_peekFlag(0), m_queueHead(0),
m_queueTail(0), m_queueMaxSize(maxQueueSize), m_nMallocResBufLen(nMallocResBufLen)
{

}

int IMP_AlgoResQueue::GetQueueLen()
{
    IMP_Lock queuelock(&m_queueLock);
    return m_nQueueLen;
}

int IMP_AlgoResQueue::InitQueue()
{
	IMP_Lock queuelock(&m_queueLock);//need this line

    m_pAlgoResArray = new IMP_AlgoRes[m_queueMaxSize];
    if (NULL == m_pAlgoResArray) {
        qDebug() << "New Algo Res Array Failed";
    } else {
        for (int i=0; i < m_queueMaxSize; i++)
        {
            m_pAlgoResArray[i].nFrameNo = 0;
            m_pAlgoResArray[i].pResult = new char[m_nMallocResBufLen];
        }
    }
	return IMP_TRUE;
}

IMP_AlgoResQueue::~IMP_AlgoResQueue()
{
	ClearQueue();
	IMP_Lock queuelock(&m_queueLock);
    if (NULL != m_pAlgoResArray)
	{
		for (int i=0; i< m_queueMaxSize; i++)
		{
            if( NULL != m_pAlgoResArray[i].pResult )
			{
                delete[] m_pAlgoResArray[i].pResult;
			}
		}
        delete[] m_pAlgoResArray;
        m_pAlgoResArray = NULL;
	}
}


int IMP_AlgoResQueue::IsEmpty()
{
	IMP_Lock queuelock(&m_queueLock);
	return (m_queueHead == m_queueTail)?IMP_TRUE:IMP_FALSE;
}

int IMP_AlgoResQueue::IsFull()
{
	IMP_Lock queuelock(&m_queueLock);
	int tailTest = (m_queueTail + 1) % m_queueMaxSize;
	return (tailTest == m_queueHead)?IMP_TRUE:IMP_FALSE;
}


IMP_AlgoRes* IMP_AlgoResQueue::GetAlgoResAddr()
{
    IMP_Lock queuelock(&m_queueLock);
    int tailTest;
    tailTest = (m_queueTail + 1) % m_queueMaxSize;
    if ( tailTest == m_queueHead )
    {
        ///IMP_LOG_DEBUG("FRAME QUEUE IS FULL");
        qDebug() << "ALGO RES QUEUE IS FULL";
        return NULL;///IMP_FALSE;//IMP_TRUE;
    }
    IMP_AlgoRes* pAlgoRes = &m_pAlgoResArray[m_queueTail];
    m_queueTail = (m_queueTail + 1) % m_queueMaxSize;
    m_nQueueLen++;
    return pAlgoRes;
}


IMP_AlgoRes* IMP_AlgoResQueue::PeekAlgoRes()
{
	IMP_Lock queuelock(&m_queueLock);
	if( m_queueHead == m_queueTail )
    {
        /**
		*pPicOutFrame = NULL;
		return IMP_FALSE;
        */
        ////qDebug() << "ALGO RES QUEUE IS EMPTY";
        return NULL;
	}
	m_peekFlag = 1;
    IMP_AlgoRes *pAlgoRes = &m_pAlgoResArray[m_queueHead];
    return pAlgoRes;
}

int IMP_AlgoResQueue::EndPeek()
{
	IMP_Lock queuelock(&m_queueLock);
	m_peekFlag = 0;
	return IMP_TRUE;
}

int IMP_AlgoResQueue::RemoveAlgoRes()
{
	IMP_Lock queuelock(&m_queueLock);
	m_peekFlag = 0;//EndPeek();
	if( m_queueHead == m_queueTail )	//add by 0416  a bug
	{
		return IMP_TRUE;
	}
	m_queueHead = (m_queueHead + 1) % m_queueMaxSize;
    m_nQueueLen--;
	return IMP_TRUE;
}

int IMP_AlgoResQueue::ClearQueue()
{
    m_nQueueLen = 0;
    m_queueHead = 0;
    m_queueTail = 0;
    return 1;
    /*
	while (1)
	{
		{
			IMP_Lock queuelock(&m_queueLock);
			if ( 0 == m_peekFlag )
			{
				m_queueHead = 0;
				m_queueTail = 0;
                qDebug() << "Test Clear Algo Res Queue Successfully";
				return IMP_TRUE;
			}
            qDebug() << "Test Clear Algo Res Queue Failed";
		}
		Sleep(4);
	}
    */
}
