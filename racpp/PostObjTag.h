#pragma once
#include <string>
class PostObjTag
{
public:
	PostObjTag(void);
	~PostObjTag(void);

	std::string getTags();
	void setTags(std::string tags);
	std::string getDeviceid();
	void setDeviceid(std::string deviceid);
	std::string getProductkey();
	void setProductkey(std::string productkey);

private:
	std::string tags;
	std::string deviceid;
	std::string productkey;
};

