#pragma once
class PostObjEvent;
class HandlerThread;
class EventController
{
public:
	EventController(void);
	~EventController(void);

	static void postEventInfo(HandlerThread* handler, PostObjEvent& event);
};

