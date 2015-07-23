#include "StdAfx.h"
#include "AndroidTools.h"


AndroidTools::AndroidTools(void)
{
}


AndroidTools::~AndroidTools(void)
{
}

int AndroidTools::hashCode( std::string str )
{
	const char* __s = str.c_str();
	unsigned long __h = 0;   
	for ( ; *__s; ++__s)  
		__h = 5*__h + *__s;
	return size_t(__h);
}
