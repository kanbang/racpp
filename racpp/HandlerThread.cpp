#include "StdAfx.h"
#include "HandlerThread.h"
#include "Mission.h"

HandlerThread::HandlerThread(void)
{
	::InitializeCriticalSection(&m_Lock);
	m_bRunning = false;
	m_stopEvent = CreateEvent(NULL, TRUE, TRUE, "");
}


HandlerThread::~HandlerThread(void)
{
	stop();

	Mission* pMiss = _pop_mission();
	while(pMiss)
	{
		delete pMiss;
		pMiss = _pop_mission();
	}

	::DeleteCriticalSection(&m_Lock);
}

void HandlerThread::post( Mission* new_pMission )
{
	_push_mission(new_pMission);
}

void HandlerThread::start()
{
	m_bRunning = true;
	ResetEvent(m_stopEvent);
	CreateThread( NULL, 0, _threadFun, this, 0, NULL);     
}

void HandlerThread::stop()
{
	m_bRunning = false;
	WaitForSingleObject(m_stopEvent, INFINITE);
}

void HandlerThread::_push_mission( Mission* mission )
{
	::EnterCriticalSection(&m_Lock);
	m_quMission.push(mission);
	::LeaveCriticalSection(&m_Lock);
}

Mission* HandlerThread::_pop_mission()
{
	::EnterCriticalSection(&m_Lock);
	if (m_quMission.empty())
	{
		::LeaveCriticalSection(&m_Lock);
		return NULL;
	}

	Mission* pMission = m_quMission.front();
	m_quMission.pop();
	::LeaveCriticalSection(&m_Lock);

	return pMission;
}

void HandlerThread::_threadRun()
{
	Mission* pMission = NULL;
	while (true)
	{
		pMission = _pop_mission();
		if (pMission)
		{
			pMission->run();
			delete pMission;
		}
		else
		{
			if (!m_bRunning)
			{
				break;
			}

			Sleep(1000);
		}
	}
	SetEvent(m_stopEvent);
}

DWORD WINAPI HandlerThread::_threadFun( LPVOID lp )
{
	HandlerThread* pThread = (HandlerThread*)lp;
	pThread->_threadRun();
	return 0;
}
