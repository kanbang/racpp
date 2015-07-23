#pragma once
#include "JSONObject.h"

class SaveInfo
{
	JSONObject m_Object;
public:
	SaveInfo(JSONObject object);
	~SaveInfo();
	void run();

public:
	static std::string getLogInfoDir();
	static std::string getLogInfoPathName();
};
