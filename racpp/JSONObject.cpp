#include "StdAfx.h"
#include "JSONObject.h"
#include "JSONArray.h"
#include "UmsAgent.h"


JSONObject::JSONObject(void)
{
}

JSONObject::JSONObject(const Object& obj)
{
	Object::operator=(obj);
}

JSONObject::JSONObject( const std::string& str )
{
	parse(str);
}

JSONObject::~JSONObject(void)
{
}

void JSONObject::put( std::string key, const JSONArray& value )
{
	import(key, (jsonxx::Array)value);
}

void JSONObject::put( std::string key, std::string value )
{
	import(key, value);
}

std::string JSONObject::getString( std::string sKey)
{
	if(has<jsonxx::String>(sKey))
		return get<std::string>(sKey);

	if(has<jsonxx::Number>(sKey))
	{
		int iNum = get<jsonxx::Number>(sKey);
		return UmsAgent::int2Str(iNum);
	}

	return "";
}

JSONArray* JSONObject::getJsonArr( const std::string& key )
{
	if(!has<jsonxx::Array>(key))
		return NULL;

	jsonxx::Array& arr = get<jsonxx::Array>(key);
	return (JSONArray*)(&arr);
}

std::string JSONObject::toString() const
{
	return json();
}
