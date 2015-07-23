#include "StdAfx.h"
#include "JSONArray.h"
#include "JSONObject.h"

JSONArray::JSONArray(void)
{
}


JSONArray::~JSONArray(void)
{
}

void JSONArray::put( int index, const JSONObject& info )
{
	import(index, (jsonxx::Object)info);
}

void JSONArray::put(const JSONObject& info)
{
	import((jsonxx::Object)info);
}
