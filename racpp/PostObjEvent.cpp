#include "StdAfx.h"
#include "PostObjEvent.h"
#include "CommonUtil.h"

PostObjEvent::PostObjEvent(void)
{
}

PostObjEvent::PostObjEvent( PostObjEvent* pEvent )
{
	if(pEvent == NULL){
		acc = "";
		label ="";
		event_id = "";
	}else{
		setVal(*pEvent);
	}
}

PostObjEvent::PostObjEvent( const PostObjEvent& event )
{
	setVal(event);
}

PostObjEvent::PostObjEvent( std::string event_id, std::string label, std::string acc )
{
	this->event_id = event_id;
	this->label = label;
	this->acc = acc;
	time = CommonUtil::getTime();
	activity = "activity";
	appkey = CommonUtil::getAppKey();
	version = CommonUtil::getCurVersion();
}

PostObjEvent::PostObjEvent( std::string event_id, std::string label, std::string acc, std::string time, std::string activity, std::string version, std::string appkey )
{
	this->event_id = event_id;
	this->label = label;
	this->acc = acc;
	this->time = time;
	this->activity = activity;
	this->version = version;
	this->appkey = appkey;
}

PostObjEvent::~PostObjEvent(void)
{
}

bool PostObjEvent::verification()
{
	if (getAcc().find("-") != -1 || getAcc().empty()) {
		//Log Log.d("test", this.getAcc());
		return false;
	} else {
		return true;
	}
}

std::string PostObjEvent::getTime()
{
	return time;
}

void PostObjEvent::setTime( std::string time )
{
	time = time;
}

std::string PostObjEvent::getActivity()
{
	return activity;
}

void PostObjEvent::setActivity( std::string activity )
{
	activity = activity;
}

std::string PostObjEvent::getVersion()
{
	return version;
}

void PostObjEvent::setVersion( std::string version )
{
	version = version;
}

std::string PostObjEvent::getAppkey()
{
	return appkey;
}

void PostObjEvent::setAppkey( std::string appkey )
{
	appkey = appkey;
}

std::string PostObjEvent::getEvent_id()
{
	return event_id;
}

void PostObjEvent::setEvent_id( std::string event_id )
{
	event_id = event_id;
}

std::string PostObjEvent::getLabel()
{
	return label;
}

void PostObjEvent::setLabel( std::string label )
{
	label = label;
}

std::string PostObjEvent::getAcc()
{
	return acc;
}

void PostObjEvent::setAcc( std::string acc )
{
	acc = acc;
}

int PostObjEvent::hashCode()
{
	const int prime = 31;
	int result = 1;
	result = prime * result + (AndroidTools::hashCode(acc));
	result = prime * result + (AndroidTools::hashCode(activity));
	result = prime * result + (AndroidTools::hashCode(appkey));
	result = prime * result + (AndroidTools::hashCode(event_id));
	result = prime * result + (AndroidTools::hashCode(label));
	result = prime * result + (AndroidTools::hashCode(time));
	result = prime * result + (AndroidTools::hashCode(version));
	return result;
}

bool PostObjEvent::equals( PostObjEvent* pObj )
{
	if (this == pObj)
		return true;
	if (pObj == NULL)
		return false;

	if (!(pObj->acc == acc))
		return false;

	if (!(pObj->activity == activity))
		return false;

	if (!(pObj->appkey == appkey))
		return false;

	if (!(pObj->event_id == event_id))
		return false;

	if (!(pObj->label == label))
		return false;

	if (!(pObj->time == time))
		return false;

	if (!(pObj->version == version))
		return false;

	return true;
}

void PostObjEvent::setVal( const PostObjEvent& res )
{
	event_id	= res.event_id;
	label		= res.label;
	acc			= res.acc;
	time		= res.time;
	activity	= res.activity;
	version		= res.version;
	appkey		= res.appkey;
}
