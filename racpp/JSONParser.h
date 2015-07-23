#pragma once
#include <string>
#include "MyMessage.h"
class JSONParser
{
public:
	JSONParser(void);
	~JSONParser(void);

	static MyMessage parse(std::string str);
};

