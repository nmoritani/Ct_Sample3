#pragma once
#include "CtObject.h"

class CtDbgClipManager :
	public CtObject
{
public:
	CtDbgClipManager();
	~CtDbgClipManager();

	static void updateClipContents(int clipNum = 9);
	static void updateInfoContents(int clipNum = 9);
	static void updateClipDelCopinfo(int selectNum = 0, int totalNum = 0);
};

