#include "StdAfx.h"
#include "UmsAgent.h"
#include "EventController.h"
#include "PostObjEvent.h"
#include "Mission.h"
#include "SaveInfo.h"
#include "AssembJSONObj.h"
#include "md5\md5lib.h"

using namespace std;

UmsAgent::UmsAgent(void) 
	: mUseLocationService(true)
	, start_millis("")
	, start(0)
	, end_millis("")
	, end(0)
	, duration("")
	, session_id("")
	, activities("")
	, appkey("")
	, stacktrace("")
	, time("")
	, os_version("")
	, deviceID("")
	, curVersion("")
	, packagename("")
	, sdk_version("")
	, mUpdateOnlyWifi(true)
	, defaultReportMode(0)
	, isPostFile(true)
	, isFirst(true)
	, UserIdentifier("userid")
	, currenttime(0)
{
	this->handler = new HandlerThread();
	this->handler->start();
}

UmsAgent::~UmsAgent(void)
{
	this->handler->stop();
	delete this->handler;
}

UmsAgent& UmsAgent::instance()
{
	static UmsAgent obj;
	return obj;
}

void UmsAgent::setBaseURL( std::string url )
{
	UmsConstants::instance().preUrl = url;
}

void UmsAgent::setSessionContinueMillis( long interval )
{
	if (interval > 0) {
		UmsConstants::instance().kContinueSessionMillis = interval;
	}
}

void UmsAgent::setAutoLocation( bool AutoLocation )
{
	mUseLocationService = AutoLocation;
}

UmsAgent& UmsAgent::getUmsAgent()
{
	return *this;
}

JSONObject UmsAgent::getClientDataJSONObject()
{
	std::string mac_ads = "00:00:00:00:00:00:00";
	vec_string vec_mac = CommonUtil::GetINETMacAddresses();
	if (!vec_mac.empty())
	{
		mac_ads = vec_mac.front();
	}

	JSONObject clientData;
	clientData.put("os_version", CommonUtil::getOsVersion());
	clientData.put("platform", "android");
	clientData.put("language", "chinese");
	clientData.put("deviceid", CommonUtil::getDeviceID());//
	clientData.put("appkey", CommonUtil::getAppKey());
	clientData.put("resolution", CommonUtil::getScreenXY());		//"1024*768"
	clientData.put("ismobiledevice", "true");
	clientData.put("phonetype", CommonUtil::getCurVersion());	//
	clientData.put("imsi", CommonUtil::getDeviceID());		//李愿军 机器码
	clientData.put("network", "wifi");			//获取网络工作模式
	clientData.put("time", CommonUtil::getTime());		//获取当前时间
	clientData.put("version", CommonUtil::getCurVersion());
	clientData.put(UserIdentifier, CommonUtil::getUserIdentifier());

	clientData.put("mccmnc", "");
	clientData.put("cellid", "");
	clientData.put("lac", "");
	clientData.put("modulename", "");
	clientData.put("devicename", CommonUtil::getCManufacturerAndProduct());//获取电脑生产厂商和型号
	clientData.put("wifimac", mac_ads);		//李愿军 获取网卡地址 ok
	clientData.put("havebt", "false");
	clientData.put("havewifi", "false");
	clientData.put("havegps", "false");
	clientData.put("havegravity", "false");//

	clientData.put("latitude", "");
	clientData.put("longitude", "");
	return clientData;
}

void UmsAgent::postTags( const std::string& tags )
{
	handler->post(new Mission_One(handler, tags));
}


void UmsAgent::postErrorInfo( std::string error )
{
	JSONObject errorInfo = AssembJSONObj::getErrorInfoJSONObj(error);
	errorInfo.put(UserIdentifier, CommonUtil::getUserIdentifier());
	if (1 == CommonUtil::getReportPolicyMode() && CommonUtil::isNetworkAvailable())
	{
		MyMessage message = NetworkUitlity::PostMsg(UmsConstants::instance().preUrl + UmsConstants::instance().errorUrl, errorInfo.toString());
		if (!message.isFlag()) {
			saveInfoToFile("errorInfo", errorInfo);
		}
	} else {
		saveInfoToFile("errorInfo", errorInfo);
	}
}

void UmsAgent::onEvent( const std::string& event_id )
{
	onEvent(event_id, 1);
}

void UmsAgent::onEvent( const std::string& event_id, const std::string& label, const int& acc )
{
	EventController::postEventInfo(handler, PostObjEvent( event_id, label, int2Str(acc)));
}

void UmsAgent::onEvent( std::string event_id, int acc )
{
	onEvent(event_id, "", acc );
}

std::string UmsAgent::int2Str( int iVal )
{
	std::stringstream ss;
	std::string sAcc;
	ss << iVal;
	ss >> sAcc;
	return sAcc;
}

void UmsAgent::update()
{
	handler->post(new Mission_Five());
}

void UmsAgent::uploadLog()
{
	handler->post(new Mission_Three());
}

void UmsAgent::setDefaultReportPolicy( int reportModel )
{
	m_reportModel = reportModel;
}

int UmsAgent::getReportPolicyMode()
{
	return m_reportModel;
}

std::string UmsAgent::generateSeesion()
{
	std::string str = CommonUtil::getAppKey() + CommonUtil::getTime();
	std::string sessionId = getMD5(str.c_str(), str.length()); 		//张修华ok
	saveSessionTime();
	return sessionId;
}

void UmsAgent::saveSessionTime()
{
	currenttime = 100;	//李愿军 获取当前毫秒数
}

void UmsAgent::uploadAllLog()
{
	std::string sFileDir = SaveInfo::getLogInfoDir();
	std::string sFilePathName = SaveInfo::getLogInfoPathName();

	std::fstream file;
	file.open(sFilePathName, ios::in, _SH_DENYRW);
	if (!file.is_open())
	{
		return;
	}

	file.seekg(0, ios::end);
	int iFileSize = file.tellg();
	char *pFileData = new char[iFileSize+1];
	file.seekg(0, ios::beg);
	file.read(pFileData, iFileSize);
	pFileData[iFileSize] = '\0';
	file.close();
	string sData = pFileData;

	if (CommonUtil::isNetworkAvailable()) 
	{
		MyMessage message = NetworkUitlity::PostMsg(UmsConstants::instance().preUrl+UmsConstants::instance().updataUrl, sData);
		if (message.isFlag()) 
		{
			if (remove(SaveInfo::getLogInfoPathName().c_str()) == 0) 
				printf("Removed %s.\n",file); 
			else 
				perror("remove"); 
		}
	}
//////////////////////////////////////////////////////////////////////////
// 	File file1 = new File(Environment.getExternalStorageDirectory().getAbsolutePath()
// 	+ "/mobclick_agent_cached_" + context.getPackageName());
// 	if (file1.exists()) {
// 	FileInputStream in = new FileInputStream(Environment.getExternalStorageDirectory()
// 	.getAbsolutePath() + "/mobclick_agent_cached_" + context.getPackageName());
// 	StringBuffer sb = new StringBuffer();
// 
// 	int i = 0;
// 	byte[] s = new byte[1024 * 4];
// 
// 	while ((i = in.read(s)) != -1) {
// 
// 	sb.append(new String(s, 0, i));
// 	}
// 	if (CommonUtil.isNetworkAvailable(context)) {
// 	MyMessage message = NetworkUitlity.post(UmsConstants::instance().preUrl
// 	+ UmsConstants::instance().uploadUrl, sb + "");
// 	if (message.isFlag()) {
// 	File file = new File(Environment.getExternalStorageDirectory()
// 	.getAbsolutePath()
// 	+ "/mobclick_agent_cached_"
// 	+ context.getPackageName());
// 	file.delete();
// 	} else {
// 	CommonUtil.printLog("uploadError", "uploadLog Error");
// 	}
// 	} else {
// 	CommonUtil.printLog("NetworkError", "Network, not work");
// 	}
// 	}	//张修华 ok
}

void UmsAgent::postClientData()
{
	if (isFirst) {
		handler->post(new Mission_Two(handler));
		isFirst = false;
	}
}

void UmsAgent::saveInfoToFile( std::string type, JSONObject info )
{
	JSONArray newdata;
	newdata.put(0, info);
	JSONObject jsonObject;
	jsonObject.put(type, newdata);
	handler->post(new Mission_Four(new SaveInfo(jsonObject)));
}

JSONObject UmsAgent::getJSONObject()
{
	JSONObject info;
	info.put("session_id", session_id);
	info.put("start_millis", start_millis);
	info.put("end_millis", end_millis);
	info.put("duration", duration);
	info.put("version", CommonUtil::getCurVersion());
	info.put("activities", activities);
	info.put("appkey", appkey);
	info.put("UserIdentifier", CommonUtil::getUserIdentifier());
	return info;
}

void UmsAgent::Init(const std::string& url, const std::string& appKey, const std::string& userId, const std::string& appVersion)
{
	setDefaultReportPolicy(1);
	setBaseURL(url);
	CommonUtil::bindUserIdentifier(userId);
	this->appkey = appKey;
	curVersion = appVersion;

	//提交之前累积的离线日志
	uploadLog();
	postClientData();
}

void UmsAgent::Close()
{
	this->handler->stop();
}


//魏光耀	
//     void onPause(const Context& context) {
//         Runnable postOnPauseinfoRunnable = new Runnable() {
// 
//             @Override
//             public void run() {
//                 postOnPauseInfo(context);
//             }
//         };
//         handler.post(postOnPauseinfoRunnable);
//     }
// 
//     private static void postOnPauseInfo(Context context) {
// 
//         saveSessionTime(context);
// 
//         end_millis = CommonUtil.getTime();
//         end = Long.valueOf(System.currentTimeMillis());
//         duration = end - start + "";
//         appkey = CommonUtil.getAppKey(context);
//         JSONObject info = getJSONObject(context);
// 
//         CommonUtil.printLog("UmsAgent", info + "");
// 
//         if (1 == CommonUtil.getReportPolicyMode(context) && CommonUtil.isNetworkAvailable(context)) {
//             CommonUtil.printLog("activityInfo", info.toString());
// 
//             MyMessage message = NetworkUitlity.post(UmsConstants::instance().preUrl + UmsConstants::instance().activityUrl,
//                     info.toString());
//             if (!message.isFlag()) {
//                 saveInfoToFile("activityInfo", info, context);
//                 CommonUtil.printLog("error", message.getMsg());
// 
//             }
//         } else {
//             saveInfoToFile("activityInfo", info, context);
//         }
// 
//     }

//魏光耀
//     void onResume(const Context& context) {
//         Runnable postOnResumeinfoRunnable = new Runnable() {
// 
//             @Override
//             public void run() {
//                 postonResume(context);
//             }
//         };
//         handler.post(postOnResumeinfoRunnable);
//     }
// 
//     /**
//      * @param context
//      */
//     private static void postonResume(Context context) {
//         if (!CommonUtil.isNetworkAvailable(context)) {
//             setDefaultReportPolicy(context, 0);
//         } else {
//             if (UmsAgent.isPostFile) {
//                 Thread thread = new GetInfoFromFile(context);
//                 thread.run();
//                 UmsAgent.isPostFile = false;
//             }
// 
//         }
// 
//         isCreateNewSessionID(context);
// 
//         activities = CommonUtil.getActivityName(context);
//         try {
//             if (session_id == null) {
//                 generateSeesion(context);
//             }
// 
//         } catch (Exception e) {
//             e.printStackTrace();
//         }
//         start_millis = CommonUtil.getTime();
//         start = Long.valueOf(System.currentTimeMillis());
// 
//     }

//     private static void isCreateNewSessionID(Context context) {
//         // TODO Auto-generated method stub
//         long currenttime = System.currentTimeMillis();
// 
//         SharedPreferences preferences = context.getSharedPreferences("UMS_session_ID_savetime",
//                 Context.MODE_PRIVATE);
//         long session_save_time = preferences.getLong("session_save_time", currenttime);
//         if (currenttime - session_save_time > UmsConstants::instance().kContinueSessionMillis) {
//             try {
//                 generateSeesion(context);
//             } catch (ParseException e) {
//                 // TODO Auto-generated catch block
//                 e.printStackTrace();
//             }
//         }
// 
//     }

//    private static void isCreateNewSessionID(Context context) {
//        // TODO Auto-generated method stub
//        long currenttime = System.currentTimeMillis();
//    
//        SharedPreferences preferences = context.getSharedPreferences("UMS_session_ID_savetime",
//                Context.MODE_PRIVATE);
//        long session_save_time = preferences.getLong("session_save_time", currenttime);
//        if (currenttime - session_save_time > UmsConstants::instance().kContinueSessionMillis) {
//            try {
//                generateSeesion(context);
//            } catch (ParseException e) {
//                // TODO Auto-generated catch block
//                e.printStackTrace();
//            }
//        }
//    
//    }
	
//     void updateOnlineConfig(const Context& context) {
// 		Runnable updateOnlineConfigRunnable = new Runnable() {
// 			@Override
// 				public void run() {
// 					updateOnlineConfigs(context);
// 			}
// 		};
// 		handler.post(updateOnlineConfigRunnable);
//     }

    /**
     * get online value by key
     * 
     * @param context
     * @param onlineKey
     * @return
     */
//     String getConfigParams(Context context,
//             String onlineKey) {
// 
//         appkey = CommonUtil.getAppKey(context);
//         JSONObject json = new JSONObject();
//         try {
//             json.put("appkey", appkey);
//         } catch (JSONException e1) {
//             e1.printStackTrace();
//         }
//         String appkeyJSON = json.toString();
//         if (CommonUtil.isNetworkAvailable(context)) {
//             MyMessage message = NetworkUitlity
//                     .post(UmsConstants::instance().preUrl + UmsConstants::instance().onlineConfigUrl, appkeyJSON);
//             if (message.isFlag()) {
//                 try {
//                     JSONObject object = new JSONObject(message.getMsg());
//                     return object.getString(onlineKey);
// 
//                 } catch (JSONException e) {
//                     e.printStackTrace();
//                 }
//             } else {
//                 CommonUtil.printLog("error", "getConfigParams error");
//             }
//         } else {
//             CommonUtil.printLog("NetworkError", "Network, not work");
//         }
//         return "";
//     }
	//魏光耀