#include "CtWindowContentsWizardMessage.h"

CtWindowContentsWizardMessage::CtWindowContentsWizardMessage(const CtWindowID WindowID) :
	CtWindowContents(WindowID) 
{
	info.type = MessageType_Dialog;
	info.bTouchErasable = false;
	info.IndicationTime = WindowContentsMessage_IndicationTime_Invalid;
	strncpy(info.d_parts.title_str,"",WindowContentsMessage_StrMaxSize);
	info.d_parts.title_str[WindowContentsMessage_StrMaxSize-1] = '\0';
	info.d_parts.title_str_id = WindowContentsMessage_StrindId_Invalid;
	strncpy(info.d_parts.msg_str,"",WindowContentsMessage_StrMaxSize);
	info.d_parts.msg_str[WindowContentsMessage_StrMaxSize-1] = '\0';
	info.d_parts.msg_str_id = WindowContentsMessage_StrindId_Invalid;
	info.d_parts.set = false;
	info.d_parts.ret = true;
	t_color = WindowContentsMessage_TelopBaseColor;
}

CtWindowContentsWizardMessage::CtWindowContentsWizardMessage(CtWindowContentsWizardMessage& message) : CtWindowContents(message.getType()) {
	setMessageInfo(message.getMessageInfo());
	setTelopColor(message.getTelopColor());
}

CtWindowContentsWizardMessage::~CtWindowContentsWizardMessage() {
}

void CtWindowContentsWizardMessage::setMessageInfo(MessageInfo *_info)
{
	if( _info == NULL ) return;
	info.type = _info->type;
	info.bTouchErasable = _info->bTouchErasable;
	info.IndicationTime = _info->IndicationTime;
	if( info.type == MessageType_Dialog){
		strncpy(info.d_parts.title_str,_info->d_parts.title_str,WindowContentsMessage_StrMaxSize);
		info.d_parts.title_str[WindowContentsMessage_StrMaxSize-1] = '\0';
		info.d_parts.title_str_id = _info->d_parts.title_str_id;
		strncpy(info.d_parts.msg_str,_info->d_parts.msg_str,WindowContentsMessage_StrMaxSize);
		info.d_parts.msg_str[WindowContentsMessage_StrMaxSize-1] = '\0';
		info.d_parts.msg_str_id = _info->d_parts.msg_str_id;
		info.d_parts.set = _info->d_parts.set;
		info.d_parts.ret = _info->d_parts.ret;
	} else if(info.type == MessageType_Telop) {
		strncpy(info.t_parts.msg_str,_info->t_parts.msg_str,WindowContentsMessage_StrMaxSize);
		info.t_parts.msg_str[WindowContentsMessage_StrMaxSize-1] = '\0';
		info.t_parts.msg_str_id = _info->t_parts.msg_str_id;
	} else {
		/* Do Nothing */
	}
}

CtWindowContentsWizardMessage::MessageInfo* CtWindowContentsWizardMessage::getMessageInfo()
{
	return &info;
}

void CtWindowContentsWizardMessage::setTelopColor(unsigned int _rgba)
{
	t_color = _rgba;
}

unsigned int CtWindowContentsWizardMessage::getTelopColor()
{
	return t_color;
}

