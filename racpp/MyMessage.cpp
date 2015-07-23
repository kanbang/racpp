#include "StdAfx.h"
#include "MyMessage.h"


MyMessage::MyMessage(void)
{
}


MyMessage::~MyMessage(void)
{
}

bool MyMessage::isFlag()
{
	return m_flag;
}

void MyMessage::setFlag( bool flag )
{
	m_flag = flag;
}

void MyMessage::setMsg( std::string msg )
{
	m_msg = msg;
}

std::string MyMessage::getMsg()
{
	return m_msg;
}
