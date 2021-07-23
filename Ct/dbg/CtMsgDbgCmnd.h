/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtMsgDbgCmnd
*/
#ifndef __CtMsgDbgCmnd_H__
#define __CtMsgDbgCmnd_H__

#include "CtMsg.h"
#include "CtComDbgThread.h"

class CtMsgDbgCmnd :
	public CtMsg
{
public:
	//CtMsgDbgCmnd(unsigned long long cmndData, unsigned char cmndDataSize = 0) ;
	CtMsgDbgCmnd(int _cmdGrp, int* _cmndData);
	~CtMsgDbgCmnd();
	/*inline unsigned long long getCmndData();
	inline unsigned int getCmndDataSize();*/
	const int* getData();
	const int getCmdGrp();
	void setData(int* _Data);
	void setCmdGrp(int _CmdGrp);
	bool sendMsg() {
		return CtComDbgThread::sendMsg(*this);
	}
private:
	//unsigned long long m_cmndData;
	//unsigned char m_CmndDataSize;
	const int* m_pData;
	int m_CmdGrp;
};


#endif // __CtMsgDbgCmnd_H__
