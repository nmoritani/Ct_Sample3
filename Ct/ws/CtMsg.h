/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMsg
 */


#ifndef __CtMsg_H__
#define __CtMsg_H__

#include "kernel.h"
#include "CtObject.h"

/// タスク間通信に使用するメッセージの抽象クラス
/// タスク間通信をするメッセージはは、このクラスから派生クラスを作成する
class CtMsg : public CtObject {
public :
    typedef struct _CtMsgHeader {
        T_MSG 		Header;
        CtMsg*	 	pMsg;
    } CtMsgHeader;
    
    ////    Constructors and destructors    ////
	CtMsg();
public :
    virtual ~CtMsg();
    
    ////    Operations    ////
    
    inline const CtMsgHeader* getMsgHeader() const;
    
private :
    CtMsgHeader m_MsgHeader;
};

inline const CtMsg::CtMsgHeader* CtMsg::getMsgHeader() const
{
    return &m_MsgHeader;
}

#endif
