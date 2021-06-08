#ifndef __CtWindowContentsWizardMessage_H__
#define __CtWindowContentsWizardMessage_H__

#include "CtWindowContents.h"
#include "CtMessageDesign.h"
#include "str_id.h"

class CtWindowContentsWizardMessage : public CtWindowContents {
public :
	#define WindowContentsMessage_StrMaxSize	30
	#define WindowContentsMessage_StrindId_Invalid	0xFFFFFFFF
	#define WindowContentsMessage_IndicationTime_Invalid	0xFFFFFFFF
	#define WindowContentsMessage_TelopBaseColor	MESSAGE_TELOP_BASE_COLOR

	typedef enum MessageType{
		MessageType_Dialog,		/* ダイアログ形式の表示 */
		MessageType_Telop,		/* テロップ形式の表示 */
	}MessageType;

	typedef struct MessageDialogParts{
		char 	title_str[WindowContentsMessage_StrMaxSize];
		int  	title_str_id;
		char 	msg_str[WindowContentsMessage_StrMaxSize];
		int  	msg_str_id;
		bool 	set;
		bool 	ret;
	}MessageDialogParts;

	typedef struct MessageTelopParts{
		char 	msg_str[WindowContentsMessage_StrMaxSize];
		int		msg_str_id;
	}MessageTelopParts;

	typedef struct MessageInfo{
		MessageType	type;
		bool bTouchErasable;
		int  IndicationTime;
		MessageDialogParts	d_parts;
		MessageTelopParts	t_parts;
	}MessageInfo;
	
	CtWindowContentsWizardMessage(const CtWindowID WindowID);
	CtWindowContentsWizardMessage(CtWindowContentsWizardMessage& message);
	virtual ~CtWindowContentsWizardMessage();

	void setMessageInfo(MessageInfo *_info);
	MessageInfo* getMessageInfo();

	void setTelopColor(unsigned int _rgba);
	unsigned int getTelopColor();

private:
	MessageInfo	info;
	unsigned int t_color;

};

#endif
