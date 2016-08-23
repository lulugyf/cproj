#include "libsys.h"

namespace NSPrime
{
ETYPE CLSemaphore::Init()
{
#ifdef __WIN__
	m_pSem=CreateSemaphore(NULL,0,0x7FFFFFFF,NULL);
	if (!m_pSem)
	{
		return ENOMEM;
	}
#else
	if (sem_init(&m_pSem,0,0) == -1)
	{
		return ENOMEM;
	}
#endif
	return 0;
}

bool CLSemaphore::Unlock()
{
#ifdef __WIN__
	return ReleaseSemaphore (m_pSem,1,NULL) == 0;
#else
	return sem_post(&m_pSem) == 0;
#endif
}
bool CLSemaphore::Lock()
{
#ifdef __WIN__
	return WaitForSingleObject(m_pSem,INFINITE) == WAIT_OBJECT_0;
#else
	return sem_wait(&m_pSem) == 0;
#endif
}
bool CLSemaphore::Term()
{
#ifdef __WIN__
	return CloseHandle(m_pSem) == TRUE;
#else
	return sem_destroy(&m_pSem) == 0;
#endif
}
}
