#include "StdAfx.h"
#include "PostObjTag.h"


PostObjTag::PostObjTag(void)
{
}


PostObjTag::~PostObjTag(void)
{
}

std::string PostObjTag::getTags()
{
	return tags;
}

void PostObjTag::setTags( std::string tags )
{
	tags = tags;
}

std::string PostObjTag::getDeviceid()
{
	return deviceid;
}

void PostObjTag::setDeviceid( std::string deviceid )
{
	deviceid = deviceid;
}

std::string PostObjTag::getProductkey()
{
	return productkey;
}

void PostObjTag::setProductkey( std::string productkey )
{
	productkey = productkey;
}
