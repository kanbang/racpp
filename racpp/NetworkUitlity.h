#pragma once

#include <string>
#include "MyMessage.h"

class NetworkUitlity
{
public:
	NetworkUitlity(void);
	~NetworkUitlity(void);

	static MyMessage PostMsg(std::string url, std::string data);
	static std::string Post(std::string url, std::string data);

	static long paramleng;
};

