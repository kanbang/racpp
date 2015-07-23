#include "StdAfx.h"
#include "AssembJSONObj.h"


AssembJSONObj::AssembJSONObj(void)
{
}


AssembJSONObj::~AssembJSONObj(void)
{
}

JSONObject AssembJSONObj::getErrorInfoJSONObj( std::string error )
{
	std::string stacktrace = error;
	std::string activities = "activity";
	std::string time = CommonUtil::getTime();
	std::string appkey = CommonUtil::getAppKey();
	std::string os_version = CommonUtil::getSdkVersion();
	std::string deviceID = CommonUtil::getDeviceID();
	JSONObject errorInfo;
	errorInfo.put("stacktrace", stacktrace);
	errorInfo.put("time", time);
	errorInfo.put("activity", activities);
	errorInfo.put("appkey", appkey);
	errorInfo.put("os_version", os_version);
	errorInfo.put("deviceid", deviceID);
	return errorInfo;
}

JSONObject AssembJSONObj::getpostTagsJSONObj( PostObjTag tagobj )
{
	JSONObject object;
	object.put("tags", tagobj.getTags());
	object.put("deviceid",tagobj.getDeviceid());
	object.put("productkey",tagobj.getProductkey());
	return object;
}

JSONObject AssembJSONObj::getEventJOSNobj( PostObjEvent event )
{
	JSONObject localJSONObject;
	localJSONObject.put("time", event.getTime());
	localJSONObject.put("version", event.getVersion());
	localJSONObject.put("event_identifier", event.getEvent_id());
	localJSONObject.put("appkey", event.getAppkey());
	localJSONObject.put("activity", event.getActivity());
	localJSONObject.put("label", event.getLabel());
	localJSONObject.put("acc", event.getAcc());
	return localJSONObject;
}
