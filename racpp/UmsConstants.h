#pragma once

#include <string>

class UmsConstants
{
	UmsConstants();
public:
	static UmsConstants& instance();

	bool DebugMode;
	long kContinueSessionMillis;

	const std::string eventUrl;
	const std::string errorUrl;
	const std::string clientDataUrl;
	const std::string updataUrl;
	const std::string activityUrl;
	const std::string onlineConfigUrl;
	const std::string uploadUrl;
	const std::string tagUser;
	std::string preUrl;
};

