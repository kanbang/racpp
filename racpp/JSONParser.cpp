#include "StdAfx.h"
#include "JSONParser.h"
#include "JSONObject.h"


JSONParser::JSONParser(void)
{
}


JSONParser::~JSONParser(void)
{
}

MyMessage JSONParser::parse( std::string str )
{
	MyMessage message;
	JSONObject jsonObject(str);
	std::string flag = jsonObject.getString("flag");
	if (atoi(flag.c_str()) > 0)
		message.setFlag(true);
	else
		message.setFlag(false);
	message.setMsg(jsonObject.getString("msg")); 
	return message;
}
