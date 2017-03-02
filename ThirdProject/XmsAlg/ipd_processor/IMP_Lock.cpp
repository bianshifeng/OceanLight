#include "IMP_Lock.h"

IMP_CriticalSection::IMP_CriticalSection()
{
    InitializeCriticalSection(&m_CritSect);
}

IMP_CriticalSection::~IMP_CriticalSection()
{
    DeleteCriticalSection(&m_CritSect);
}

void IMP_CriticalSection::Lock()
{
    EnterCriticalSection(&m_CritSect);
}

void IMP_CriticalSection::Unlock()
{
    LeaveCriticalSection(&m_CritSect);
}


IMP_Mutex::IMP_Mutex()
{
	hMutex=::CreateMutex(NULL, FALSE, NULL);
}

IMP_Mutex::IMP_Mutex(const char * pMutexName)
{
	if (NULL != pMutexName)
	{
        hMutex=::CreateMutexA(NULL, FALSE, pMutexName);
	}
	else
	{
        hMutex=::CreateMutexA(NULL, FALSE, NULL);
	}
}

IMP_Mutex::~IMP_Mutex()
{
	if( hMutex )
	{
		::CloseHandle(hMutex);
	}
	
}

void IMP_Mutex::Lock()
{
	::WaitForSingleObject(hMutex, INFINITE);
}

void IMP_Mutex::Unlock()
{
	::ReleaseMutex(hMutex);
}



IMP_Lock::IMP_Lock(LockableObject* pLockable)
{
	m_pLockable = NULL;
	if ( NULL != pLockable )
	{
		m_pLockable = pLockable;
		m_pLockable->Lock();
	}
}

IMP_Lock::~IMP_Lock()
{
	if ( NULL != m_pLockable )
	{
		m_pLockable->Unlock();
	}
}
