#pragma once
#include <string>
#include "AndroidTools.h"
class PostObjEvent
{
public:
	PostObjEvent(void);
	~PostObjEvent(void);

	PostObjEvent(PostObjEvent* pEvent);
	PostObjEvent(const PostObjEvent& event);
	PostObjEvent(std::string event_id, std::string label, std::string acc);
	PostObjEvent(std::string event_id, std::string label, std::string acc, std::string time, std::string activity, std::string version, std::string appkey);
	bool verification();
	std::string getTime();
	void setTime(std::string time);
	std::string getActivity();
	void setActivity(std::string activity);
	std::string getVersion();
	void setVersion(std::string version);
	std::string getAppkey();
	void setAppkey(std::string appkey);
	std::string getEvent_id();
	void setEvent_id(std::string event_id);
	std::string getLabel();
	void setLabel(std::string label);
	std::string getAcc();
	void setAcc(std::string acc);
	int hashCode();
	bool equals(PostObjEvent* pObj);

private:
	void setVal(const PostObjEvent& res);

private:
	std::string event_id;
	std::string label;
	std::string acc;
	std::string time;
	std::string activity;
	std::string version;
	std::string  appkey;
};

