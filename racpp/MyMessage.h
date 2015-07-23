#pragma once

#include <string>

class MyMessage
{
public:
	MyMessage(void);
	~MyMessage(void);

	bool isFlag();
	void setFlag(bool flag);
	std::string getMsg();
	void setMsg(std::string msg);

private:
	bool m_flag;
	std::string m_msg;
};

