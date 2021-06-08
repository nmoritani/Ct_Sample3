#pragma once
#ifndef __CtDbgWidgetTree_H__
#define __CtDbgWidgetTree_H__

#include "CtObject.h"
#include "CtVector.h"
#ifdef WIN32_GUI_SIM
#include <windows.h>
#include "resource.h"
#endif

class CtDbgWidgetTree : CtObject
{
public:
	
	typedef void (*Func)();
	typedef struct CtDbgWidgetTreeData {
		int depth;
		int widgetAdr;
		char WidgetType[32];
		int Size_x;
		int Size_y;
		int region_x;
		int region_y;
		int region_w;
		int region_h;
		int screen;
		bool visible;
		bool trans;
		int ParentWidgetAdr;
		CtDbgWidgetTreeData() {
			memset(this, 0, sizeof(CtDbgWidgetTreeData));
		}

	}CtDbgWidgetTreeData;

	~CtDbgWidgetTree();
	
	static CtDbgWidgetTree* getInstance() {
		if (m_pThis == NULL) {
			m_pThis = new CtDbgWidgetTree();
		}
		return m_pThis;
	}

#ifdef WIN32_GUI_SIM
	void registCreateFinCall(unsigned int _hwnd) {
		refresh();
		this->hwnd = (HWND)_hwnd;
	}
#else

	void registCreateFinCall(Func pFunc) {
		CallBackFunc = pFunc;
	}

#endif
	void CallSimFunc() {
#ifdef WIN32_GUI_SIM
		PostMessage(hwnd, WM_COMMAND, IDC_TREE_DATA, 0);
#else
		if (CallBackFunc != NULL) {
			CallBackFunc();
		}
#endif
	}
	void endCreateTreeData() {
		CallSimFunc();
	}
	int getTreeDataSize() {
		return m_DataList.size() - 1;
	}
	void setTreeData(CtDbgWidgetTreeData& _Node) {
		// Dataê›íË
		CtDbgWidgetTreeData* pNode = new CtDbgWidgetTreeData(_Node);
		m_DataList.push_back(pNode);
	}
	CtDbgWidgetTreeData* getTreeData(int _Index) {
		if (m_DataList.size() <= 0) return NULL;
		if (_Index < 0 || m_DataList.size() <= _Index) return NULL;
		return m_DataList[_Index];
	}
	void refresh() {
		m_DataList.clear();
	}
private:
#ifdef WIN32_GUI_SIM
	HWND hwnd;
#endif

	static CtDbgWidgetTree* m_pThis;
	Func CallBackFunc;
	CtDbgWidgetTree();
	CtVector::Vector<CtDbgWidgetTreeData*> m_DataList;
};
#endif
