#pragma once
#include "json\jsonxx.h"


class JSONObject;
class JSONArray : public jsonxx::Array
{
public:
	JSONArray(void);
	~JSONArray(void);

	void put(int index, const JSONObject& info);
	void put(const JSONObject& info);
};

