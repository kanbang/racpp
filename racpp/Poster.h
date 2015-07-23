#pragma once

#include <string>
#include "PostObjTag.h"
#include "PostObjEvent.h"

class Poster
{
public:
	Poster(void);
	~Poster(void);

	static PostObjTag GenerateTagObj(const std::string& tags);
	static PostObjEvent GenerateEventObj(const PostObjEvent& event);
};

