#pragma once
#include "UmsConstants.h"
#include "HandlerThread.h"
#include "SCell.h"
#include "JSONObject.h"
#include "CommonUtil.h"
#include "MyMessage.h"
#include "NetworkUitlity.h"
#include "JSONArray.h"
#include "racppExports.h"

class RACPP_EXTERN UmsAgent
{
private:
	UmsAgent();
	~UmsAgent();
    bool mUseLocationService;
    std::string start_millis;// The start time point
    long start;
    std::string end_millis;// The end time point
    long end;//
    std::string duration;// run time
    std::string session_id;
    std::string activities;// currnet activity's name
    std::string appkey;
	std::string stacktrace;// error info
    std::string time; // error time
    std::string os_version;
    std::string deviceID;

    std::string curVersion;// app version
	std::string packagename;// app packagename
    std::string sdk_version;// Sdk version

    bool mUpdateOnlyWifi;
    int defaultReportMode;// 0 send at next time's defaultmode
                              // 1 send at now
    bool isPostFile;
    bool isFirst;
    std::string UserIdentifier;

	HandlerThread* handler;
	int m_reportModel;
	long currenttime;

public:
	static UmsAgent& instance();

public:
	void Init(const std::string& url, const std::string& appKey, const std::string& userId, const std::string& appVersion);
	void Close();

public:
	void onEvent(const std::string& event_id);
	void onEvent(const std::string& event_id, const std::string& label, const int& acc);
	void onEvent(std::string event_id, int acc);
	void postErrorInfo(std::string error);

public:
	JSONObject getClientDataJSONObject();
	void uploadAllLog();

private:
	friend class CommonUtil;
	std::string getAppVersion() const { return curVersion; }
	std::string getAppkey() const { return appkey; }
    void setSessionContinueMillis(long interval);
    void setAutoLocation(bool AutoLocation);
    UmsAgent& getUmsAgent();
    void postTags(const std::string& tags);
    void saveInfoToFile(std::string type, JSONObject info);
    JSONObject getJSONObject();
    void update();
	int getReportPolicyMode();
    std::string generateSeesion();
    void saveSessionTime();

public:
	static std::string int2Str(int iVal);

private:
	void uploadLog();
	void postClientData();
	void setBaseURL(std::string url);
	void setDefaultReportPolicy(int reportModel);
};


