#ifndef __CtWindowContentsDispMessage_H__
#define __CtWindowContentsDispMessage_H__

#include "CtWindowContents.h"

class CtWindowContentsDispMessage : public CtWindowContents {
public :
	
	CtWindowContentsDispMessage(const CtWindowID WindowID);
	CtWindowContentsDispMessage(CtWindowContentsDispMessage& message);
	virtual ~CtWindowContentsDispMessage();

	//結果通知メッセージ用(APL⇒GUIへの通知)
	void setMessage(const char* message);								//APL側：出したいメッセージをセットする(メッセージを出さない場合はNULL)
																		//英数字のみ使用可能。改行コード(\n)は使用可能(ただし、10行まで)
	const char* getMessage();											//GUI側：メッセージがNULL以外なら半透明黒背景にして文字を画面中央に表示する

private:
	char m_message[50];
};

#endif
