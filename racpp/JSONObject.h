#pragma once
#include <string>
#include "json\jsonxx.h"
using namespace jsonxx;

class JSONArray;
class JSONObject : public Object	//ÕÅÐÞ»ª ok
{
public:
	JSONObject(void);
	JSONObject(const Object& obj);
	JSONObject(const std::string& str);
	~JSONObject(void);

	std::string toString() const;	
	void put(std::string key, std::string value);
	void put(std::string key, const JSONArray& value);
	std::string getString(std::string sKey);
	JSONArray* getJsonArr(const std::string& key);
};

