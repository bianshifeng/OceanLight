#ifndef  __IMP_FRAME_QUEUE_H__
#define  __IMP_FRAME_QUEUE_H__

#include "IMP_Lock.h"
#include "IMP_Frame.h"

#define DEFAULT_MAX_FRAME_QUEUE_SIZE		15
#define DEFAULT_MALLOC_WIDTH				1920
#define DEFAULT_MALLOC_HEIGHT				1080
#define ALGO_RESULT_DATA_SIZE				1000


class IMP_FrameQueue
{
public:
	IMP_FrameQueue();
    explicit IMP_FrameQueue(int maxQueueSize, int nMallocWidth, int nMallocHeight);
	~IMP_FrameQueue();

	int InitFrameQueue();
	
    int GetFrameQueueLen();

	int IsEmpty();
	int IsFull();

	///////int PushFrame(IMP_Codec*);			/////????? IMP_Codec
	IMP_PicOutFrame* GetFrameAddr();
    /////char* GetFrameResAddr();
	
	int PeekFrame(IMP_PicOutFrame** pPicOutFrame);
	int EndPeek();
	int RemoveFrame();

	int ClearQueue();

    IMP_PicOutFrame* FindMatchFrameAddr(int nFrameNo);

private:
	IMP_CriticalSection m_queueLock;
	IMP_PicOutFrame		*m_pArrayFrames;

	volatile int m_peekFlag;	//1:peeking using		0:not used
	volatile int m_queueHead;
	volatile int m_queueTail;		
	
	int m_queueMaxSize;		//队列的最大长度
	int m_nMallocWidth;
	int m_nMallocHeight;
    int m_nQueueLen;

};

#endif
