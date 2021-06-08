/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtBuilderKeyboard
 */


#ifndef __CtBuilderKeyboard_H__
#define __CtBuilderKeyboard_H__

#include "CtWindow.h"
#include "CtKeyboardInfo.h"
#include "CtWindowContentsFileInfo.h"

#include "CtContainerMenuTitle.h"

//					KEYBOARD‚ ‚é‚È‚¢‘Œ©•\
 //[A-a]a - z && A - z‚È‚ç‚ ‚é/[123#]1 - 0 && (A - Z || a - z)‚È‚ç‚ ‚é

//			A - Z	a - z	1 - 0	'.' - '-'	space	©	¨	A - a	123#
//FULL		›		›		›		›			›		›	›	›		›
//FILE		›		~		›		'.'ˆÈŠO		›		›	›	~		›
//PASSWORD	›		›		›		›			~		~	~	›		›
//USERPASS	›		›		›		›			~		~	~	›		›
//IP		~		~		›		'.'			~		›	›	~		~
//ALPHA		›		~		~		~			~		›	›	~		~
//NUMBER	~		~		›		~			~		›	›	~		~

class CtBuilderKeyboard : public CtObject
{
/*** ƒƒ\ƒbƒh ***********************************/
public:
	CtBuilderKeyboard(CtWindowID id);
	~CtBuilderKeyboard();

	void setContents(CtWindowContents* pContents);
	CtLayout* createLayout();

	inline CtTextField*    getTextField();
	inline CtStackLabel*   getKeyboard();
	inline CtToggleButton* getCaps();
	inline CtButton*       getBS();
	inline CtButton*       getRet();
	inline CtToggleButton* getKigou();
	inline CtButton*       getSpace();
	inline CtButton*       getLeft();
	inline CtButton*       getRight();
	inline CtButton*       getEnter();

private:

	CtLayout* createController();

	CtLayout*    createTextField();
	CtLayout*    createTextField_BackGround();
	CtTextField* createTextField_BackGround_Text();
	
	CtLayout* createKeyboard();

	CtLayout* createLargeStr();
	CtLayout* createSmallStr();
	CtLayout* createSymbols();
	CtLayout* createSymbols2();
	CtLayout* createFuncKey();

	void createOthersKey();

	void getText(char* str);

protected:

/*** ƒƒ“ƒo   ***********************************/
public:

private:
	CtWindowID					m_WindowId;
	CtWindowContentsFileInfo* m_pFileContents;
	CtKeyboardInfo::CtKeyboardInfoItem* m_info;


	CtTextField*    m_pText;
	CtStackLabel*	m_pKeyboard;

	CtToggleButton* m_pCaps;		// CtToggleButton
	CtButton*       m_pBS;
	CtButton*       m_pRet;
	CtToggleButton* m_pKigou;       // CtToggleButton
	CtButton*       m_pSpace;
	CtButton*       m_pLeft;
	CtButton*       m_pRight;
	CtButton*       m_pEnter;


protected:

};
inline CtTextField* CtBuilderKeyboard::getTextField()
{
	return m_pText;
}
inline CtStackLabel* CtBuilderKeyboard::getKeyboard()
{
	return m_pKeyboard;
}
inline CtToggleButton* CtBuilderKeyboard::getCaps()
{
	return m_pCaps;
}
inline CtButton* CtBuilderKeyboard::getBS()
{
	return m_pBS;
}
inline CtButton* CtBuilderKeyboard::getRet()
{
	return m_pRet;
}
inline CtToggleButton* CtBuilderKeyboard::getKigou()
{
	return m_pKigou;
}
inline CtButton* CtBuilderKeyboard::getSpace()
{
	return m_pSpace;
}
inline CtButton* CtBuilderKeyboard::getLeft()
{
	return m_pLeft;
}
inline CtButton* CtBuilderKeyboard::getRight()
{
	return m_pRight;
}
inline CtButton* CtBuilderKeyboard::getEnter()
{
	return m_pEnter;
}

#endif
