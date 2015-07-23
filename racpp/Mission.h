#pragma once
#include <string>
#include "PostObjEvent.h"
class HandlerThread;

class Mission
{
public:
	Mission(void) {}
	virtual ~Mission(void) {}

	virtual void run() = 0;
};

class Mission_One : public Mission
{
public:
	Mission_One(HandlerThread* hander, std::string tags);
	~Mission_One() {}

	virtual void run();

private:
	HandlerThread* m_Hander;
	std::string m_Tags;
};

class Mission_Two : public Mission
{
public:
	Mission_Two(HandlerThread* hander);
	~Mission_Two() {}

	virtual void run();
private:
	HandlerThread* m_Hander;
};

class Mission_Three : public Mission
{
public:
	Mission_Three() {}
	~Mission_Three() {}

	virtual void run();
};

class SaveInfo;
class Mission_Four : public Mission
{
public:
	Mission_Four(SaveInfo* pSaveInfo);
	~Mission_Four();

	virtual void run();
private:
	SaveInfo* m_pSaveInfo;
};

class Mission_Five : public Mission
{
public:
	Mission_Five() {}
	~Mission_Five() {}

	virtual void run();
};

class Mission_Event : public Mission
{
public:
	Mission_Event(HandlerThread* handler, PostObjEvent& event);

	virtual void run();

private:
	PostObjEvent		m_event;
	HandlerThread*		m_handler;
};
