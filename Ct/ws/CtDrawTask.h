/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	Drawタスククラス
*/

#include "CtMsgDrawTask.h"
#include "CtMsg.h"
#include "Ct.h"
#include "CtDraw.h"


class CtDrawTask : public CtObject
{
public:
	virtual ~CtDrawTask();
	static CtDrawTask* getInstance();

	void loop();
	void wake();

private:
	CtDrawTask();
	
	void wait(FLGPTN &flg);
	void drawFast(int Screen);

	CtDraw* m_pDraw;
	CtWindowController* m_pWinCtrl;

	static CtDrawTask* m_pInstance;
};
