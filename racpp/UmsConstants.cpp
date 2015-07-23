#include "StdAfx.h"
#include "UmsConstants.h"


UmsConstants::UmsConstants(void)
	: DebugMode(true)
	, kContinueSessionMillis(30000L)
	, eventUrl("/ums/postEvent")
	, errorUrl("/ums/postErrorLog")
	, clientDataUrl("/ums/postClientData")
	, updataUrl("/ums/getApplicationUpdate")
	, activityUrl("/ums/postActivityLog")
	, onlineConfigUrl("/ums/getOnlineConfiguration")
	, uploadUrl("/ums/uploadLog")
	, tagUser("/ums/postTag")
{

}

UmsConstants& UmsConstants::instance()
{
	static UmsConstants obj;
	return obj;
}
