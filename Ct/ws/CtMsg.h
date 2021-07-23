/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMsg
 */


#ifndef __CtMsg_H__
#define __CtMsg_H__

#include "CtObject.h"

/// タスク間通信に使用するメッセージの抽象クラス
/// タスク間通信をするメッセージはは、このクラスから派生クラスを作成する
class CtMsg : public CtObject {
public :

	CtMsg();
	CtMsg(int Priority);
	
	int getPriority();
	void setPriority(int Priority);
	
public :
    virtual ~CtMsg();
	
private :
	int		m_Priority;
};

#endif
