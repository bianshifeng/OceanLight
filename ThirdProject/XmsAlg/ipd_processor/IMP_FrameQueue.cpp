#include "QDebug"
#include "IMP_FrameQueue.h"

#include "imp_algo_type.h"



IMP_FrameQueue::IMP_FrameQueue():m_nQueueLen(0), m_peekFlag(0), m_queueHead(0), m_queueTail(0), m_queueMaxSize(DEFAULT_MAX_FRAME_QUEUE_SIZE),
m_nMallocWidth(DEFAULT_MALLOC_WIDTH), m_nMallocHeight(DEFAULT_MALLOC_HEIGHT)
{

}

IMP_FrameQueue::IMP_FrameQueue(int maxQueueSize, int nMallocWidth, int nMallocHeight):m_nQueueLen(0), m_peekFlag(0), m_queueHead(0),
m_queueTail(0), m_queueMaxSize(maxQueueSize), m_nMallocWidth(nMallocWidth), m_nMallocHeight(nMallocHeight)
{

}

int IMP_FrameQueue::GetFrameQueueLen()
{
    IMP_Lock queuelock(&m_queueLock);
    return m_nQueueLen;
}

int IMP_FrameQueue::InitFrameQueue()
{
	IMP_Lock queuelock(&m_queueLock);//need this line

	m_pArrayFrames = new IMP_PicOutFrame[m_queueMaxSize];
	if (NULL == m_pArrayFrames) 
	{
		///IMP_LOG_ERROR("New Array Frame Failed");
		qDebug() << "New Array Frame Failed";
	}
	
    int nImgSize = m_nMallocWidth * m_nMallocHeight * 4;
	for (int i=0; i<m_queueMaxSize; i++)
	{
		m_pArrayFrames[i].nWidth = m_nMallocWidth;
		m_pArrayFrames[i].nHeight = m_nMallocHeight;
        m_pArrayFrames[i].pu8D1 = new uchar[nImgSize];
        m_pArrayFrames[i].pu8D2 = m_pArrayFrames[i].pu8D1 + m_pArrayFrames[i].nWidth * m_pArrayFrames[i].nHeight;
        m_pArrayFrames[i].pu8D3 = m_pArrayFrames[i].pu8D2 + m_pArrayFrames[i].nWidth * m_pArrayFrames[i].nHeight / 4;
		m_pArrayFrames[i].pResult = new char[ALGO_RESULT_DATA_SIZE];
		m_pArrayFrames[i].nFrameNo = 0;
        m_pArrayFrames[i].nFrameTime = 0;
        m_pArrayFrames[i].nUseFlag = 0;
        m_pArrayFrames[i].nResFlag = 0;
        m_pArrayFrames[i].nImgFormat = IMG_FORMAT_RGB;
	}

	return IMP_TRUE;
}

IMP_FrameQueue::~IMP_FrameQueue()
{
	ClearQueue();
	IMP_Lock queuelock(&m_queueLock);
	if (NULL != m_pArrayFrames)
	{
		for (int i=0; i< m_queueMaxSize; i++)
		{
            if( NULL != m_pArrayFrames[i].pu8D1 )
			{
                delete[] m_pArrayFrames[i].pu8D1;
				delete[] m_pArrayFrames[i].pResult;
			}
		}
		delete[] m_pArrayFrames;
		m_pArrayFrames = NULL;
	}
}


int IMP_FrameQueue::IsEmpty()
{
	IMP_Lock queuelock(&m_queueLock);
	return (m_queueHead == m_queueTail)?IMP_TRUE:IMP_FALSE;
}

int IMP_FrameQueue::IsFull()
{
	IMP_Lock queuelock(&m_queueLock);
	int tailTest = (m_queueTail + 1) % m_queueMaxSize;
	return (tailTest == m_queueHead)?IMP_TRUE:IMP_FALSE;
}

IMP_PicOutFrame* IMP_FrameQueue::GetFrameAddr()
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
    IMP_PicOutFrame* pOutFrame = &m_pArrayFrames[m_queueTail];
    m_queueTail = (m_queueTail + 1) % m_queueMaxSize;
    m_nQueueLen++;
    return pOutFrame;
}


IMP_PicOutFrame* IMP_FrameQueue::FindMatchFrameAddr(int nFrameNo)
{
    IMP_Lock queuelock(&m_queueLock);
    int i;
    IMP_PicOutFrame* ret = NULL;
    if(m_queueHead < m_queueTail) {
        for(i=m_queueHead; i< m_queueTail; i++) {
            if(m_pArrayFrames[i].nFrameNo == nFrameNo) {
                ret = &m_pArrayFrames[i];
                break;
            }
        }
    }else if(m_queueHead > m_queueTail){
        for(i=m_queueHead; i<m_queueMaxSize; i++) {
            if(m_pArrayFrames[i].nFrameNo == nFrameNo) {
                ret = &m_pArrayFrames[i];
                break;
            }
        }
        for(i=0; i<m_queueTail; i++ ) {
            if(m_pArrayFrames[i].nFrameNo == nFrameNo) {
                ret = &m_pArrayFrames[i];
                break;
            }
        }
    }
    return ret;
}

int IMP_FrameQueue::PeekFrame(IMP_PicOutFrame** pPicOutFrame)
{
	IMP_Lock queuelock(&m_queueLock);
	if( m_queueHead == m_queueTail )
	{
		*pPicOutFrame = NULL;
		return IMP_FALSE;
	}
	m_peekFlag = 1;
	*pPicOutFrame=&m_pArrayFrames[m_queueHead];
	return IMP_TRUE;
}

int IMP_FrameQueue::EndPeek()
{
	IMP_Lock queuelock(&m_queueLock);
	m_peekFlag = 0;
	return IMP_TRUE;
}

int IMP_FrameQueue::RemoveFrame()
{
	IMP_Lock queuelock(&m_queueLock);
	m_peekFlag = 0;//EndPeek();
	if( m_queueHead == m_queueTail )	//add by 0416  a bug
	{
		return IMP_TRUE;
	}
    m_pArrayFrames[m_queueHead].nUseFlag = 0;
    m_pArrayFrames[m_queueHead].nResFlag = 0;
	m_queueHead = (m_queueHead + 1) % m_queueMaxSize;
    m_nQueueLen--;
	return IMP_TRUE;
}

int IMP_FrameQueue::ClearQueue()
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
