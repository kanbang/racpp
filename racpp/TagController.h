#pragma once

#include <string>
#include "CommonUtil.h"
#include "AssembJSONObj.h"
#include "JSONObject.h"
#include "Poster.h"
#include "NetworkUitlity.h"
#include "JSONParser.h"
#include "MyMessage.h"

class HandlerThread;
class TagController
{
	TagController();
	~TagController();
	const std::string POSTURL;
public:
	static TagController& instance();
	void PostTag(std::string tags, HandlerThread* handler);
};

