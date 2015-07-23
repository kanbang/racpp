#include "StdAfx.h"
#include "TagController.h"
#include "UmsConstants.h"


TagController::TagController(void)
	: POSTURL(UmsConstants::instance().preUrl+UmsConstants::instance().tagUser)
{
}


TagController::~TagController(void)
{
}

TagController& TagController::instance()
{
	static TagController obj;
	return obj;
}

void TagController::PostTag( std::string tags, HandlerThread* handler )
{
	JSONObject object = AssembJSONObj::getpostTagsJSONObj(Poster::GenerateTagObj(tags));
	if (1 == CommonUtil::getReportPolicyMode()
		&& CommonUtil::isNetworkAvailable()) {
			std::string result = NetworkUitlity::Post(POSTURL, object.toString());
			MyMessage message = JSONParser::parse(result);
			if (!message.isFlag()) {
				CommonUtil::saveInfoToFile(handler,"tags", object);
			}
	} else {
		CommonUtil::saveInfoToFile(handler,"tags", object);
	}
}
