#include "QDebug"
#include "IMP_StringQueue.h"

IMP_StringQueue::IMP_StringQueue():m_nQueueLen(0), m_peekFlag(0), m_queueHead(0), m_queueTail(0), m_queueMaxSize(DEFAULT_MAX_QUEUE_SIZE)
{

}

int IMP_StringQueue::GetQueueLen()
{
    IMP_Lock queuelock(&m_queueLock);
    return m_nQueueLen;
}

int IMP_StringQueue::InitQueue()
{
    IMP_Lock queuelock(&m_queueLock);//need this line

    m_pArray = new IMP_PFR_PATH[m_queueMaxSize];
    if (NULL == m_pArray)
    {
        ///IMP_LOG_ERROR("New Array Frame Failed");
        qDebug() << "New Array Frame Failed";
    }
    for(int i = 0; i < m_queueMaxSize; i ++)
    {
        m_pArray[i].path = (char*)malloc(256);
        m_pArray[i].name = (char*)malloc(256);
        m_pArray[i].pathlen = 0;
        m_pArray[i].namelen = 0;
    }
    return IMP_TRUE;
}

IMP_StringQueue::~IMP_StringQueue()
{
    ClearQueue();
    IMP_Lock queuelock(&m_queueLock);
    if (NULL != m_pArray)
    {
        for (int i=0; i< m_queueMaxSize; i++)
        {
            if( NULL != m_pArray[i].path )
            {
                free(m_pArray[i].path);
                m_pArray[i].path = NULL;
                free(m_pArray[i].name);
                m_pArray[i].name = NULL;
            }
        }
        delete[] m_pArray;
        m_pArray= NULL;
    }
}


int IMP_StringQueue::IsEmpty()
{
    IMP_Lock queuelock(&m_queueLock);
    return (m_queueHead == m_queueTail)?IMP_TRUE:IMP_FALSE;
}

int IMP_StringQueue::IsFull()
{
    IMP_Lock queuelock(&m_queueLock);
    int tailTest = (m_queueTail + 1) % m_queueMaxSize;
    return (tailTest == m_queueHead)?IMP_TRUE:IMP_FALSE;
}

IMP_PFR_PATH* IMP_StringQueue::GetFrameAddr()
{
    IMP_Lock queuelock(&m_queueLock);
    int tailTest;
    tailTest = (m_queueTail + 1) % m_queueMaxSize;
    if ( tailTest == m_queueHead )
    {
        ///IMP_LOG_DEBUG("FRAME QUEUE IS FULL");
        //qDebug() << "FRAME QUEUE IS FULL";
        return NULL;///IMP_FALSE;//IMP_TRUE;
    }
    IMP_PFR_PATH* pOutFrame = &m_pArray[m_queueTail];
    m_queueTail = (m_queueTail + 1) % m_queueMaxSize;
    m_nQueueLen++;
    return pOutFrame;
}



int IMP_StringQueue::Peek(IMP_PFR_PATH** pPicOutFrame)
{
    IMP_Lock queuelock(&m_queueLock);
    if( m_queueHead == m_queueTail )
    {
        *pPicOutFrame = NULL;
        return IMP_FALSE;
    }
    m_peekFlag = 1;
    *pPicOutFrame=&m_pArray[m_queueHead];
    return IMP_TRUE;
}

int IMP_StringQueue::EndPeek()
{
    IMP_Lock queuelock(&m_queueLock);
    m_peekFlag = 0;
    return IMP_TRUE;
}

int IMP_StringQueue::Remove()
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

int IMP_StringQueue::ClearQueue()
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

            m_nQueueLen = 0; // added by cw 2016/01/03

            if ( 0 == m_peekFlag )
            {
                m_queueHead = 0;
                m_queueTail = 0;
                /////IMP_LOG_DEBUG("Test Clear Queue Successfully");
                qDebug() << "Test Clear Frame Queue Successfully";
                return IMP_TRUE;
            }
            /////IMP_LOG_DEBUG("Test Clear Queue Failed");
            qDebug() << "Test Clear Frame Queue Failed";
        }
        Sleep(4);
    }
    */
}
