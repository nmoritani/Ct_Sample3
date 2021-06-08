/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowDistResult
*/


#ifndef __CtFactWindowDistResult_H__
#define __CtFactWindowDistResult_H__

#include "CtWindowCommon.h"
#include "CtWindowContentsDistResultInfo.h"

class CtFactWindowDistResult : public CtWindowMain
{
public:
	CtFactWindowDistResult(CtWindowContents *pContents);
	~CtFactWindowDistResult();
	CtWindow* createWindow();

private:

	CtWindow *m_pWin;

private:
	bool destroyWindow();
	bool setContents(const CtWindowContents * pContents);
	CtWindowContentsDistResultInfo* m_pContent;
};

#endif
