#include "CtDbgWidgetTree.h"

CtDbgWidgetTree* CtDbgWidgetTree::m_pThis(NULL); /* static pointer */

CtDbgWidgetTree::CtDbgWidgetTree()
{
	m_pThis = NULL;
	CallBackFunc = NULL;
	m_DataList.resize(0);
}

CtDbgWidgetTree::~CtDbgWidgetTree()
{
	m_pThis = NULL;
	CallBackFunc = NULL;
	m_DataList.clear();
}

