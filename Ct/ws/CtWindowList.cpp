/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowList
 */


#include "CtWindowList.h"

// CtWindowList�N���X�̃f�o�b�O�o�͗L��
#define CTWINDOWLIST_DEBUGPRINT

#ifdef CTWINDOWLIST_DEBUGPRINT
#define CtWindowListPrint(...) CtDebugPrint(CtDbg, __VA_ARGS__)
#else
#define CtWindowListPrint(...)
#endif

CtWindowList::CtWindowList(int popupLimit, int changeLimit) :
m_PopupLimit(popupLimit),
m_ChangeLimit(changeLimit),
m_List(0)
{
	setClassType(CtClassType_WindowList);
}

CtWindowList::~CtWindowList()
{
	m_List.clear();
}

/* �w�肵��ID�̃E�B���h�E�擾 */
CtWindowMain* CtWindowList::get(CtWindowID id) const
{
	int top, tail;
	return get(id, top, tail);
}

/* �w�肵��ID�̃E�B���h�E�ƍ��W���擾 */
CtWindowMain* CtWindowList::get(CtWindowID id, int& top_pos, int& tail_pos) const
{
	if(m_List.empty()) return NULL;
	
	top_pos  = 0;
	for( WindowListcItr Itr = m_List.begin(); Itr != m_List.end(); ++Itr, ++top_pos){

		tail_pos = 0;
		for( TargetListcItr itr = (*Itr).begin(); itr != (*Itr).end(); ++itr, ++tail_pos ){
			if( (*itr)->getWindowID() == id ){
				return *itr;
			}
		}

	}
	return NULL;
}

/* �w�肵���ʒu�̃E�B���h�E���擾 */
CtWindowMain* CtWindowList::get(WindowPosition pos) const
{
	int top, tail;
	return get(pos, top, tail);
}

/* �w�肵���ʒu�̃E�B���h�E�ƍ��W���擾 */
CtWindowMain* CtWindowList::get(WindowPosition pos, int& top_pos, int& tail_pos) const
{
	TargetList    List;
	TargetListItr itr;
	
	if(m_List.empty()) return NULL;
	
	// Top or Bottom
	if( pos & Tops ){
		top_pos  = m_List.size() - 1;
		List     = *--m_List.end();
	}else{
		top_pos  = 0;
		List     = *m_List.begin();
	}
	
	// Tail or Head
	if( pos & Tails ){
		tail_pos = List.size() - 1;
		itr      = --List.end();
	}else{
		tail_pos = 0;
		itr      = List.begin();
	}
	
	return *itr;
}

/* �w�肵�����W�̃E�B���h�E���擾 */
CtWindowMain* CtWindowList::get(int top_pos, int tail_pos) const
{
	int top, tail;

	if ( m_List.empty() ) return NULL;

	top = 0;
	for (WindowListcItr Itr = m_List.begin(); Itr != m_List.end(); ++Itr, ++top) {
		
		tail = 0;
		for (TargetListcItr itr = (*Itr).begin(); itr != (*Itr).end(); ++itr, ++tail) {
			if (top == top_pos && tail == tail_pos) {
				return *itr;
			}
		}

	}
	return NULL;
}

bool CtWindowList::changeWindow(CtWindowMain* window)
{
	/*
	+------------+---------+
	| Win-1-2(C) | Win-1-1 |
	+------------+---------+
        changeWindow()
            ��
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+

	*(C) : �J�����g

	*/

	CtWindowListPrint("%s(%08x)\n", __PRETTY_FUNCTION__, window);

	TargetList List;
	
	if (m_List.empty()){
		//���߂Ă̓o�^
		List.push_front(window);
		m_List.push_front(List);
	}else{
		List = *--m_List.end();
		if ( List.size() >= m_ChangeLimit ) return false;
		List.push_front(window);
		*--m_List.end() = List;
	}
	
	//�f�o�b�O���O�\��
	printWinodwList();
	
	return true;
}

bool CtWindowList::popupWindow(CtWindowMain* window)
{
	/*
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+
        popupWindow()
            ��
	+------------+
	| Win-2-1(C) |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+

	*(C) : �J�����g

	*/

	CtWindowListPrint("%s(%08x)\n", __PRETTY_FUNCTION__, window);

	TargetList List;

	if ( m_List.size() >= m_PopupLimit ) return false;

	List.push_front(window);
	m_List.push_back(List);
	
	//�f�o�b�O���O�\��
	printWinodwList();
	
	return true;
}
bool CtWindowList::swapWindow(CtWindowMain* window)
{
	/*
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+
        swapWindow()
            ��
	+------------+---------+---------+
	| Win-1-4(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+

	*(C) : �J�����g

	*/

	CtWindowListPrint("%s(%08x)\n", __PRETTY_FUNCTION__, window);

	TargetList List;

	if (m_List.empty()) {
		//���߂Ă̓o�^
		List.push_front(window);
		m_List.push_front(List);
	}
	else {
		List = *--m_List.end();
		List.pop_front();
		List.push_front(window);
		*--m_List.end() = List;
	}

	//�f�o�b�O���O�\��
	printWinodwList();
	
	return true;
}

bool CtWindowList::returnWindow()
{
	/*
	+------------+---------+---------+
	| Win-3-3(C) | Win-3-2 | Win-3-1 |
	+------------+---------+---------+
	| Win-2-3(C) | Win-2-2 | Win-2-1 |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+
        returnWindow()
            ��
	+------------+---------+
	| Win-3-2(C) | Win-3-1 |
	+------------+---------+---------+
	| Win-2-3(C) | Win-2-2 | Win-2-1 |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+

	*(C) : �J�����g

	*/

	CtWindowListPrint("%s()\n", __PRETTY_FUNCTION__);

	TargetList List;
	
	List = *--m_List.end();
	
	if ( List.size() <= 1 ) return false;
	
	List.pop_front();
	*--m_List.end() = List;
	
	//�f�o�b�O���O�\��
	printWinodwList();
	
	return true;
}

bool CtWindowList::closeWindow(CtWindowID id)
{
	/*
	+------------+---------+---------+
	| Win-3-3(C) | Win-3-2 | Win-3-1 |
	+------------+---------+---------+
	| Win-2-3(C) | Win-2-2 | Win-2-1 |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+
        closeWindow(Win-2-3)
            ��
	+------------+---------+---------+
	| Win-3-3(C) | Win-3-2 | Win-3-1 |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+

	*(C) : �J�����g

	*/

	CtWindowListPrint("%s()\n", __PRETTY_FUNCTION__);

	if ( m_List.empty() ) return false;
	
	bool ret = false;

	for( WindowListItr Itr = m_List.begin(); Itr != m_List.end(); ++Itr ){
		for( TargetListItr itr = (*Itr).begin(); itr != (*Itr).end(); itr++ ){
			if ( id == (*itr)->getWindowID() ){
				m_List.erase(Itr);
				
				//�f�o�b�O���O�\��
				printWinodwList();
				
				return true;
			}
		}
	}
	return false;
}

bool CtWindowList::removeWindow(CtWindowID id)
{
	/*
	���p�^�[��1
	+------------+---------+---------+
	| Win-3-3(C) | Win-3-2 | Win-3-1 |
	+------------+---------+---------+
	| Win-2-3(C) | Win-2-2 | Win-2-1 |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+
        removeWindow(Win-2-1)
            ��
	+------------+---------+---------+
	| Win-3-3(C) | Win-3-2 | Win-3-1 |
	+------------+---------+---------+
	| Win-2-3(C) | Win-2-2 |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+


	���p�^�[��2
	+------------+---------+---------+
	| Win-3-3(C) | Win-3-2 | Win-3-1 |
	+------------+---------+---------+
	| Win-2-1(C) |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+
        removeWindow(Win-2-1)
            ��
	+------------+---------+---------+
	| Win-3-3(C) | Win-3-2 | Win-3-1 |
	+------------+---------+---------+
	| Win-1-3(C) | Win-1-2 | Win-1-1 |
	+------------+---------+---------+

	*(C) : �J�����g

	*/

	CtWindowListPrint("%s()\n", __PRETTY_FUNCTION__);

	bool ret = false;

	for(WindowListItr Itr = m_List.begin(); Itr != m_List.end(); ++Itr ){
		for( TargetListItr itr = (*Itr).begin(); itr != (*Itr).end(); itr++ ){
			if ( (*itr)->getWindowID() == id ){
				(*Itr).erase(itr);
				ret = true;
				break;
			}
		}
		if ((*Itr).empty()){
			m_List.erase(Itr);
			break;
		}
		if(ret){
			break;
		}
	}
	
	//�f�o�b�O���O�\��
	printWinodwList();
	
	return ret;
}

/*
 �J�����g�E�B���h�E���X�g�̎擾
 ���w�̃E�B���h�E�����w�֏���
*/
const CtWindowList::WindowList& CtWindowList::getWidnowList() const
{
	return m_List;
}

/*** �f�o�b�O���O�\�� ***/
void CtWindowList::printWinodwList()
{
#ifdef CTWINDOWLIST_DEBUGPRINT
	char tmp[512];
	char tmp2[32];
	const CtWindowMain *pWin;

	CtDebugPrint(CtDbg, "---- WindowList(CurrentSize:%2d) ----\n", m_List.size());
	
	for (WindowListrItr Itr = m_List.rbegin(); Itr != m_List.rend(); Itr++ ){
		tmp[0] = '\0';
		for(TargetListItr itr = (*Itr).begin(); itr != (*Itr).end(); ++itr ){
			pWin = *itr;
			sprintf(tmp2, " %08x(%#010x) |", (unsigned int)pWin, (pWin ? pWin->getWindowID() : 0));
			strcat(tmp, tmp2);
		}
		CtDebugPrint(CtDbg, "%s\n", tmp);
	}
	CtDebugPrint(CtDbg, "------------------------------------\n");

#endif
}
