#include "CtWindowContentsDispMessage.h"

CtWindowContentsDispMessage::CtWindowContentsDispMessage(const CtWindowID WindowID) : CtWindowContents(WindowID) {
	//メッセージの初期化
	memset(m_message, 0, sizeof(m_message));
	
}



CtWindowContentsDispMessage::CtWindowContentsDispMessage(CtWindowContentsDispMessage& content) : CtWindowContents(content.getType()) {
	setMessage(content.getMessage());
}



CtWindowContentsDispMessage::~CtWindowContentsDispMessage() {
}

void CtWindowContentsDispMessage::setMessage(const char * message)
{
	if( message != NULL ){
		memcpy(m_message, message, sizeof(m_message));
	} else {
		memset(m_message, 0, sizeof(m_message));
	}
	m_message[sizeof(m_message) - 1] = NULL;
}

const char * CtWindowContentsDispMessage::getMessage()
{
	return m_message;
}

