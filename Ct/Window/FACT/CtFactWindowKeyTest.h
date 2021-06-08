/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactKeyTestBase
*/


#ifndef __CtFactKeyTestBase_H__
#define __CtFactKeyTestBase_H__

#include "CtWindowCommon.h"
#include "CtWindowContentsFactKey.h"
#include "CtFactKeyTestLabel.h"

class CtFactWindowKeyTest : public CtWindowMain
{
public:
	CtFactWindowKeyTest(CtWindowID id, CtWindowContents *pContents);
	~CtFactWindowKeyTest();
	CtLayout * CreateItemLayout(const char * ucStr, CtLabel * label1, CtLabel * label2, CtLabel * label3);
	virtual bool handleKeyEvent(const CtEventKey & Key);
	virtual bool handleTouchEvent(const CtEventTouch & Touch);

private:
#define FACT_KEYTEST_ITEM_MAX (14)	//1âÊñ Ç…ìoò^â¬î\Ç»çÄñ⁄ÇÃêî = 14å¬Ç‹Ç≈ÅB
	CtWindow *m_pWin;

	CtFactKeyTestLabel *m_label_items[14];


	CtButton *m_left_top;	/* pgr2224 */
	CtButton *m_left_bottom;	/* pgr2224 */
	CtButton *m_right_top;	/* pgr2224 */
	CtButton *m_right_bottom;	/* pgr2224 */
	CtButton *m_center;	/* pgr2224 */

	CtLayout *m_layout_left_top;
	CtLayout *m_layout_left_bottom;
	CtLayout *m_layout_right_top;
	CtLayout *m_layout_right_bottom;
	CtLayout *m_layout_center;

	CtWindowContentsFactKey *m_contents_left_top;
	CtWindowContentsFactKey *m_contents_left_bottom;
	CtWindowContentsFactKey *m_contents_right_top;
	CtWindowContentsFactKey *m_contents_right_bottom;
	CtWindowContentsFactKey *m_contents_center;

	bool m_IsFinish;

	bool m_TouchAdjust;
	CtWindowContentsFactKey::FACT_TOUCH_POS m_TouchPos;

private:
	CtWindow* createWindow();
	CtLayout * createAdjustButton(CtButton * _button);
	CtLayout * CreateKeyTestLayout(int startIndex, int count);
	bool destroyWindow();

	virtual bool updateContents();
	bool setContents(const CtWindowContents * pContents);

	void SetKeyResult(const CtWindowContents * pContents);

	void SetTouchResult(const CtWindowContents * pContents);

	void SetResultMessage(const CtWindowContents * pContents);

};

#endif
