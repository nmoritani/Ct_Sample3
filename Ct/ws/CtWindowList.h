/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowList
 */


#ifndef __CtWindowList_H__
#define __CtWindowList_H__

#include "CtObject.h"
#include "CtWindowMain.h"
#include "CtList.h"

class CtWindowList : public CtObject
{
public :
	
	typedef CtList::list<CtWindowMain*>						TargetList;
	typedef CtList::list<CtWindowMain*>::iterator           TargetListItr;
	typedef CtList::list<CtWindowMain*>::reverse_iterator   TargetListrItr;
	typedef CtList::list<CtWindowMain*>::const_iterator     TargetListcItr;
	typedef CtList::list<TargetList>						WindowList;
	typedef CtList::list<TargetList>::iterator				WindowListItr;
	typedef CtList::list<TargetList>::reverse_iterator		WindowListrItr;
	typedef CtList::list<TargetList>::const_iterator		WindowListcItr;

	CtWindowList(int popupLimit = 100, int changeLimit = 100);
	virtual ~CtWindowList();

	enum WindowPosition {
		Bottom_Head = 0x00,
		Bottom_Tail = 0x01,
		Top_Head    = 0x10,
		Top_Tail    = 0x11,
		Tails       = 0x0F,
		Tops        = 0xF0,
		Current     = Top_Head,
		Root        = Bottom_Head,
		End         = Top_Tail,
	};

	CtWindowMain* get(CtWindowID id) const;
	CtWindowMain* get(CtWindowID id, int& top_pos, int& tail_pos) const;
	CtWindowMain* get(WindowPosition pos) const;
	CtWindowMain* get(WindowPosition pos, int& top_pos, int& tail_pos) const;
	CtWindowMain* get(int top_pos, int tail_pos) const;

	const WindowList& getWidnowList() const;

	bool changeWindow(CtWindowMain* window);
	bool popupWindow(CtWindowMain* window);
	bool swapWindow(CtWindowMain* window);
	bool returnWindow();
	bool closeWindow(CtWindowID id);
	bool removeWindow(CtWindowID id);
	
private :
	unsigned int m_PopupLimit;  			//!< PopupWindow�ő吔
	unsigned int m_ChangeLimit; 			//!< ChangeWindow�ő吔

	WindowList m_List;

	void printWinodwList();
};

#endif
