#ifndef _IMP_LOCK_H_
#define _IMP_LOCK_H_
#include <Windows.h>

class LockableObject
{
    public:
        LockableObject(){}
        virtual ~LockableObject(){}
        virtual void Lock() = 0;
        virtual void Unlock() = 0;
};


class IMP_CriticalSection : public LockableObject
{
    public:
        IMP_CriticalSection();
        virtual ~IMP_CriticalSection();
        virtual void Lock();
        virtual void Unlock();

    private:
        CRITICAL_SECTION m_CritSect;
};


class IMP_Lock
{
    public:
        IMP_Lock(LockableObject* pLockable);
        ~IMP_Lock();

    private:
        LockableObject* m_pLockable;
};


class IMP_Mutex : public LockableObject
{
public:
	IMP_Mutex();
	IMP_Mutex(const char * pMutexName);
	virtual ~IMP_Mutex();
	virtual void Lock();
	virtual void Unlock();
private:
	HANDLE hMutex;
};



#endif
