#pragma once

#include <string>
#include "JSONObject.h"
#include "CommonUtil.h"
#include "PostObjTag.h"
#include "PostObjEvent.h"

class AssembJSONObj
{
public:
	AssembJSONObj(void);
	~AssembJSONObj(void);

	static JSONObject getErrorInfoJSONObj(std::string error);
	static JSONObject getpostTagsJSONObj(PostObjTag tagobj);
	static JSONObject getEventJOSNobj(PostObjEvent event);
};

