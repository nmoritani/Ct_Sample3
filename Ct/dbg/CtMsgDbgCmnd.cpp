#include "CtMsgDbgCmnd.h"
//
//CtMsgDbgCmnd::CtMsgDbgCmnd(unsigned long long cmndData, unsigned char cmndDataSize) :
//	CtMsg()//,
//	/*m_cmndData(cmndData),
//	m_CmndDataSize(cmndDataSize)*/
//{
//	setClassType(CtClassType_MsgDbgCommand);
//}

CtMsgDbgCmnd::CtMsgDbgCmnd(int _CmdGrp, int* _CmndData) :	CtMsg()
{
	m_CmdGrp = _CmdGrp;
	m_pData = _CmndData;
	setClassType(CtClassType_MsgDbgCommand);
}

CtMsgDbgCmnd::~CtMsgDbgCmnd()
{
}
void CtMsgDbgCmnd::setData(int* _pData) {
	m_pData = _pData;
}

void CtMsgDbgCmnd::setCmdGrp(int _CmdGrp) {
	m_CmdGrp = _CmdGrp;
}

const int* CtMsgDbgCmnd::getData() {
	return m_pData;
}
const int CtMsgDbgCmnd::getCmdGrp() {
	return m_CmdGrp;
}
