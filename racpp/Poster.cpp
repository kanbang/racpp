#include "StdAfx.h"
#include "Poster.h"
#include "CommonUtil.h"


Poster::Poster(void)
{
}


Poster::~Poster(void)
{
}

PostObjTag Poster::GenerateTagObj( const std::string& tags )
{
	PostObjTag obj;
	obj.setTags(tags);
	obj.setProductkey(CommonUtil::getAppKey());
	obj.setDeviceid(CommonUtil::getDeviceID());
	return obj;
}

PostObjEvent Poster::GenerateEventObj( const PostObjEvent& event )
{
	PostObjEvent event2 = new PostObjEvent(event);
	event2.setActivity("activity");
	event2.setAppkey(CommonUtil::getAppKey());
	event2.setTime(CommonUtil::getTime());
	event2.setVersion(CommonUtil::getCurVersion());
	return event2;
}
