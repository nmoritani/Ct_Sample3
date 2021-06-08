/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowInitialResult
*/


#ifndef __CtFactWindowInitialResult_H__
#define __CtFactWindowInitialResult_H__

#include "CtWindowCommon.h"
#include "CtWindowContentsInitialResult.h"

class CtFactWindowInitialResult : public CtWindowMain
{
public:
	CtFactWindowInitialResult(CtWindowContents *pContents);
	~CtFactWindowInitialResult();
	CtWindow* createWindow();

private:

	CtWindow *m_pWin;

private:
	bool destroyWindow();

	bool setContents(const CtWindowContents * pContents);

	CtWindowContentsInitialResult* m_pContent;

};

#endif
