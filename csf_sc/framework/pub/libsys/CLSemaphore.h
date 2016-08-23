#pragma once

namespace NSPrime
{
	class CLSemaphore
	{
	public:
		ETYPE Init();

		bool Unlock();
		
		bool Lock();
		
		bool Term();
	private:
#ifdef __WIN__
		HANDLE m_pSem;
#else
		sem_t m_pSem;
#endif
	};
}
