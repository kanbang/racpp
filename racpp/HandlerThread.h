#pragma once
#include <queue>

class Mission;
class HandlerThread		//ÕÅÐÞ»ª ok
{
public:
	HandlerThread(void);
	~HandlerThread(void);

	void post(Mission* new_pMission);
	void start();
	void stop();

private:
	void _push_mission(Mission* mission);
	Mission* _pop_mission();
	void	 _threadRun();

private:
	static DWORD WINAPI _threadFun(LPVOID lp);

private:
	bool					m_bRunning;
	HANDLE					m_stopEvent;
	CRITICAL_SECTION		m_Lock;
	std::queue<Mission*>	m_quMission;
};

