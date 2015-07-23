#include "StdAfx.h"
#include "Mission.h"
#include "TagController.h"
#include "UmsAgent.h"
#include "JSONObject.h"
#include "SaveInfo.h"

Mission_One::Mission_One( HandlerThread* hander, std::string tags ) : m_Hander(hander), m_Tags(tags)
{

}

void Mission_One::run()
{
	TagController::instance().PostTag(m_Tags, m_Hander);
}

void Mission_Two::run()
{
	JSONObject clientData = UmsAgent::instance().getClientDataJSONObject();
	if (1 == CommonUtil::getReportPolicyMode() && CommonUtil::isNetworkAvailable()) {
			MyMessage message = NetworkUitlity::PostMsg(UmsConstants::instance().preUrl + UmsConstants::instance().clientDataUrl, clientData.toString());
			if (!message.isFlag()) {
				CommonUtil::saveInfoToFile(m_Hander, "clientData", clientData);
			}
	} else {
		CommonUtil::saveInfoToFile(m_Hander, "clientData", clientData);
	}
}

Mission_Two::Mission_Two( HandlerThread* hander ) : m_Hander(hander)
{

}

void Mission_Three::run()
{
	UmsAgent::instance().uploadAllLog();
}

void Mission_Four::run()
{
	m_pSaveInfo->run();
}

Mission_Four::~Mission_Four()
{
	delete m_pSaveInfo;
}

Mission_Four::Mission_Four( SaveInfo* pSaveInfo ) : m_pSaveInfo(pSaveInfo)
{

}

void Mission_Five::run()
{
	std::string appkey = CommonUtil::getAppKey();

	std::string curVersion = CommonUtil::getCurVersion();

	JSONObject updateObject;

	updateObject.put("appkey", appkey);
	updateObject.put("version_code", curVersion);

	if (CommonUtil::isNetworkAvailable()) 
	{
		/*MyMessage message = */NetworkUitlity::PostMsg(UmsConstants::instance().preUrl + UmsConstants::instance().updataUrl, updateObject.toString());

//		以下是根据服务器返回的信息自动更新的功能
// 		if (message.isFlag()) 
// 		{
// 			JSONObject object(message.getMsg());
// 			std::string flag = object.getString("flag");
// 			if (atoi(flag.c_str()) > 0) 
// 			{
// 				std::string fileurl = object.getString("fileurl");
// 				std::string msg = object.getString("msg");
// 				std::string forceupdate = object.getString("forceupdate");
// 				std::string description = object.getString("description");
// 				std::string time = object.getString("time");
// 				std::string version = object.getString("version");
// 				UpdateManager manager = new UpdateManager(version, forceupdate,
// 					fileurl, description);
// 				manager.showNoticeDialog();
// 			}
// 		} 
// 		else 
// 		{
// 			CommonUtil.printLog("error", message.getMsg());
// 		}
	}
	//张修华 ok
}

Mission_Event::Mission_Event( HandlerThread* handler, PostObjEvent& event )
	: m_event(event)
	, m_handler(handler)
{

}

void Mission_Event::run()
{
	if (!m_event.verification())
		return;

	JSONObject localJSONObject = AssembJSONObj::getEventJOSNobj( m_event);

	if (1 == CommonUtil::getReportPolicyMode() && CommonUtil::isNetworkAvailable()) 
	{
		std::string reslut = NetworkUitlity::Post(UmsConstants::instance().preUrl+UmsConstants::instance().eventUrl, localJSONObject.toString());
		MyMessage info = JSONParser::parse(reslut);
		if (!info.isFlag()) {
			CommonUtil::saveInfoToFile(m_handler, "eventInfo", localJSONObject);
			return;
		}
	}
}
