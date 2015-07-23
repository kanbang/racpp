#include "StdAfx.h"
#include "EventController.h"
#include "HandlerThread.h"
#include "PostObjEvent.h"
#include "JSONObject.h"
#include "AssembJSONObj.h"
#include "NetworkUitlity.h"
#include "UmsConstants.h"
#include "JSONParser.h"
#include "Mission.h"


EventController::EventController(void)
{
}


EventController::~EventController(void)
{
}

void EventController::postEventInfo( HandlerThread* handler, PostObjEvent& event )
{
	handler->post(new Mission_Event(handler, event));
}
